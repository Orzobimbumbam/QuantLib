//
// Created by Alberto Campi on 14/04/2018.
//
#define BOOST_TEST_MODULE UTests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <random>
#include "../QuantLibIncludes.h"


namespace utf = boost::unit_test;
namespace tt = boost::test_tools;
using namespace math;
using namespace common;
using namespace pricing;

const std::string actualPath = "../BOOST.TESTS/Actual/";
const std::string expectedPath = "../BOOST.TESTS/Expected/";
const std::string inputsPath = "../BOOST.TESTS/Inputs/";

BOOST_AUTO_TEST_SUITE(PayOffSpecs)
    BOOST_AUTO_TEST_CASE(Call_Put_HappyPath)
    {
        double strike = 50.0;
        boost::gregorian::date D1(2018, boost::date_time::Apr, 26);
        std::pair<boost::gregorian::date, double> p = std::make_pair(D1, 100.0);
        const std::map<boost::gregorian::date, double> spot = {p};

        PayOffCall poCallITM(strike);
        PayOffPut poPutOTM(strike);
        BOOST_CHECK_EQUAL(poCallITM(spot), 50.0);
        BOOST_CHECK_EQUAL(poPutOTM(spot), 0.0);

        strike = 150.0;
        PayOffCall poCallOTM(strike);
        PayOffPut poPutITM(strike);
        BOOST_CHECK_EQUAL(poCallOTM(spot), 0.0);
        BOOST_CHECK_EQUAL(poPutITM(spot), 50.0);

    }

    BOOST_AUTO_TEST_CASE(ArithmeticAsian_PutCall)
    {
        double strike = 50.0, _spot = 1;
        PathMap spot;
        LookAtDateArray lookAtDates;
        boost::gregorian::date D1(2018, boost::date_time::Apr, 26);

        for (unsigned long i = 0; i < 100; ++i)
        {
            const boost::gregorian::date D = D1 + boost::gregorian::days(i);
            const double s = _spot + i;
            spot.insert(std::make_pair(D, s));

            if (i%2 == 1)
                lookAtDates.push_back(D);
        }

        PayOffArithmeticAsianCall poaac(strike, lookAtDates);
        PayOffArithmeticAsianPut poaap(strike, lookAtDates);
        double expectedPoCall = 1, expectedPoPut = 0;
        BOOST_CHECK_EQUAL(poaac.payOff(spot), expectedPoCall);
        BOOST_CHECK_EQUAL(poaap.payOff(spot), expectedPoPut);

        LookAtDateArray dummy;
        PayOffArithmeticAsianCall dummyPo(strike, dummy);
        BOOST_CHECK_THROW(dummyPo.payOff(spot), std::overflow_error);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Statistics)
    BOOST_AUTO_TEST_CASE(Stat_Mean_Variance_Correlation_HappyPath, *utf::tolerance(0.1))
    {
        const int statisticsDimension = 3;
        Stat s(statisticsDimension);

        static std::mt19937 x(1), y(2), z(3); //use different seeds to reduce serial correlation
        std::normal_distribution<double> N52(5.0,2.0); //mean = 5, stdDev = 2
        std::normal_distribution<double> N01(0,1.0); //mean = 0, stdDev = 1
        std::normal_distribution<double> N11(11.5,7.2); //mean = 5, stdDev = 2

        const int NTrials = 1000;

        for (unsigned int i = 0; i < NTrials; ++i)
        {
            std::vector<double> rv = { N52(x), N01(y), N11(z) };
            s.add(rv);
        }

        Matrix covMat = s.covariance();
        std::vector<double> expMean = {5.0, 0.0, 11.5}, expVariance = {2.0*2.0, 1.0, 7.2*7.2},
        expStdDev = {2.0, 1.0, 7.2}, expStdErr = {2.0/sqrt(NTrials), 1.0/sqrt(NTrials), 7.2/sqrt(NTrials)};

        std::vector<std::vector<double>> expCov = {{2.0*2.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0 , 7.2*7.2}};
        std::vector<std::vector<double>> expCorr = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0 , 1.0}};

        BOOST_TEST(s.mean() == expMean, tt::per_element());
        BOOST_TEST(s.variance() == expVariance, tt::per_element());
        BOOST_TEST(s.stdDev() == expStdDev, tt::per_element());
        BOOST_TEST(s.stdError() == expStdErr, tt::per_element());

        for (unsigned int i = 0; i < statisticsDimension; ++i)//assert by row
        {
            BOOST_TEST(s.covariance()[i] == expCov[i], tt::per_element());
            BOOST_TEST(s.correlation()[i] == expCorr[i], tt::per_element());
        }
    }

    BOOST_AUTO_TEST_CASE(StatOneDim_Mean_Variance_HappyPath, *utf::tolerance(0.1))
    {
        StatOneDim sod;
        static std::mt19937 x;
        std::normal_distribution<double> N11(11.5,7.2); //mean = 5, stdDev = 2
        const int NTrials = 1000;

        for (unsigned int i = 0; i < NTrials; ++i)
        {
            sod.add(N11(x));
        }

        BOOST_TEST(sod.mean() == 11.5);
        BOOST_TEST(sod.stdDev() == 7.2);
        BOOST_TEST(sod.variance() == 7.2*7.2);
        BOOST_TEST(sod.stdError() == 7.2/sqrt(NTrials));
    }

    BOOST_AUTO_TEST_CASE(Stat_Exception)
    {
        const int statisticsDimension = 3;
        Stat s(statisticsDimension);
        StatOneDim sod;

        Array a = {1, 2, 3, 4}; //array size exceeds statistics dimension

        BOOST_CHECK_THROW(s.mean(), std::overflow_error);
        BOOST_CHECK_THROW(sod.variance(), std::overflow_error);
        BOOST_CHECK_THROW(s.add(a), std::out_of_range);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(NLSolver_NumQuadrature)
    struct TestFixture
    {
        double parabola(double x) const {return x*x;};
        double shiftedParabola(double x) const {return x*x - 1;};
        double cubic (double x) const {return x*x*x;};
        double derivativeCubic(double x) const {return 3*x*x;};
        double f(double x) const {return 1/(x*x);};
        double gaussian(double x) const {return math::stdNormPdf(x);};
    };

    BOOST_AUTO_TEST_CASE(NLSolver_HappyPath, *utf::tolerance(0.001))
    {
        const double yprecision = 1e-9;
        TestFixture fix;
        NLSolver<TestFixture, &TestFixture::shiftedParabola> s1(yprecision);
        NLSolver<TestFixture, &TestFixture::cubic, &TestFixture::derivativeCubic> s2(yprecision);

        BOOST_TEST(s1.solveByBisection(fix, 0, -0.5, 5) == (double)(1));
        BOOST_TEST(s2.solveByNewtonRaphson(fix, 0, 10) == (double)(0));
    }

    BOOST_AUTO_TEST_CASE(NumQuadrature_HappyPath, *utf::tolerance(0.001))
    {
        const double h = 0.01;
        TestFixture fix;
        NumQuadrature<TestFixture, &TestFixture::parabola> nq1(h);
        NumQuadrature<TestFixture, &TestFixture::cubic> nq2(h);

        NumQuadrature<TestFixture, &TestFixture::f> nqRomberg;
        NumQuadrature<TestFixture, &TestFixture::gaussian> nqRombergGauss;


        const double a = -1, b = 1, c = 2;
        const double exactParabolaIntegral = 2./3.;
        const double exactCubicIntegral = 0.0;
        const double exactFIntegral = 1./2;
        double tolerance = 1e-5;

        const double midpointParabolaIntegral = nq1.integrateByMidPoint(fix, a, b);
        const double trapezoidParabolaIntegral = nq1.integrateByTrapezoid(fix, a, b);
        const double simpsonParabolaIntegral = nq1.integrateBySimpson(fix, a, b);
        const double midpointCubicIntegral = nq2.integrateByMidPoint(fix, a, b);
        const double trapezoidCubicIntegral = nq2.integrateByTrapezoid(fix, a, b);
        const double simpsonCubicIntegral = nq2.integrateBySimpson(fix, a, b);
        const double rombergFIntegral = nqRomberg.integrateByAdaptiveRomberg(fix, b, c, tolerance);

        BOOST_TEST(midpointParabolaIntegral == exactParabolaIntegral);
        BOOST_TEST(trapezoidParabolaIntegral == exactParabolaIntegral);
        BOOST_TEST(simpsonParabolaIntegral == exactParabolaIntegral);

        BOOST_TEST(midpointCubicIntegral == exactCubicIntegral);
        BOOST_TEST(trapezoidCubicIntegral == exactCubicIntegral);
        BOOST_TEST(simpsonCubicIntegral == exactCubicIntegral);

        BOOST_TEST(std::abs(rombergFIntegral - exactFIntegral) < tolerance);

        tolerance = 1e-8;
        const double rombergGaussIntegral = nqRombergGauss.integrateByAdaptiveRomberg(fix, a, b, tolerance);
        BOOST_TEST(std::abs(rombergGaussIntegral - std::erf(1/sqrt(2))) < tolerance);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DayCountConvention)
    BOOST_AUTO_TEST_CASE(DayCountConventionHelper_happyPath)
    {
        using namespace boost::gregorian;

        DayCountConventionHelper dchSimple(Simple), dchActual(Act_Act);
        std::string d1 = "2018/4/26", d2 = "2019/5/1";
        date D1(2018, Apr, 26), D2(2019, May, 01), D3(2018, Sep, 30);

        double expectedYearCount = 370./365; //actual and simple
        BOOST_CHECK_EQUAL(dchSimple.getLengthInYears(D1, D2), expectedYearCount);
        BOOST_CHECK_EQUAL(dchActual.getLengthInYears(D1, D2), expectedYearCount);
        BOOST_CHECK_EQUAL(dchSimple.getLengthInYears(D1, D3), dchActual.getLengthInYears(D1, D3));

        date D4(2020, Aug, 01);
        expectedYearCount = 1 + (250./365 + 213./366); //actual, 2020 is a leap year
        double expectedYearCountSimple = 828./365; //simple
        BOOST_CHECK_EQUAL(dchSimple.getLengthInYears(D1, D4), expectedYearCountSimple);
        BOOST_CHECK_EQUAL(dchActual.getLengthInYears(D1, D4), expectedYearCount);

        date D5(2021, Aug, 01);
        expectedYearCount = 153./366 + 212./365;
        BOOST_CHECK_EQUAL(dchActual.getLengthInYears(D4, D5), expectedYearCount);

        date D6(2019, Jan, 01), D7(2021, Jan, 01);
        expectedYearCount = 2.;
        BOOST_CHECK_EQUAL(dchActual.getLengthInYears(D6, D7), expectedYearCount);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(BlackScholesPricerTest)
    BOOST_AUTO_TEST_CASE(BlackScholesPricer_happyPath, *utf::tolerance(1e-5))
    {
        using namespace boost::gregorian;

        double spot = 100, strike = 50, r = 0.01, sigma = 0.25;
        const date D1(2018, Apr, 26), D2(2019, May, 01);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);

        BlackScholesPricer bspc(spot, sigma, r, od, strike, Call);
        BlackScholesPricer bspp(spot, sigma, r, od, strike, Put);
        //const double T = od.getOptionYearsToMaturity();
        const double expectedCallPrice = 50.517944, expectedPutPrice = 0.013656;
        BOOST_TEST(bspc.optionPrice() == expectedCallPrice);
        BOOST_TEST(bspp.optionPrice() == expectedPutPrice);
        BOOST_TEST(bspc.putCallParity(bspc.optionPrice()) == bspp.optionPrice());
    }

    BOOST_AUTO_TEST_CASE(GeneralisedBlackScholesPricer_happyPath)
    {
        using namespace boost::gregorian;

        const double a = 0.1, b = 0.1, c = 0.1, d = 0.1;

        const double spot = 100., strike = 50.;
        const date D1(2018, Apr, 26), D2(2019, May, 01);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);

        ParametricGeneralisedVolatility sigma_t(od, a, b, c, d);

        const long size = (D2 - D1).days();
        const double h = od.getOptionYearsToMaturity()/size;

        //create random map of interest rates
        IRMap ir;
        static std::mt19937 u;
        double t = 0;
        for (unsigned long i = 0; i < size; ++i)
        {
            t += h;
            ir.insert(std::make_pair(t, static_cast<double>(u())/u.max()*0.1));
        }

        ShortRate ir_t(ir);
        GeneralisedBlackScholesPricer gbspc(spot, sigma_t, ir_t, od, strike, Call);
        BlackScholesPricer bspc(spot, gbspc.getRMSSquaredVolatility(), gbspc.getAverageRate(), od, strike, Call);

        BOOST_CHECK_EQUAL(gbspc.getRMSSquaredVolatility(), sigma_t.getRMSSquaredVolatility());
        BOOST_CHECK_EQUAL(gbspc.getAverageRate(), ir_t.getAverageRate());
        BOOST_CHECK_EQUAL(gbspc.optionPrice(), bspc.optionPrice());

    }

    BOOST_AUTO_TEST_CASE(BlackPricer_happyPath, *utf::tolerance(1e-13))
    {
        using namespace boost::gregorian;

        const double spot = 100., strike = 50., r = 0.01, sigma = 0.25;
        const date D1(2018, Apr, 26), D2(2019, May, 01);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);

        const MoneyMarketAccount mma(r);

        double F = spot*exp(r*od.getOptionYearsToMaturity());
        BlackPricer bpc(F, sigma, mma, od, strike, Call);
        BlackPricer bpp(F, sigma, mma, od, strike, Put);

        BlackScholesPricer bspc(spot, sigma, r, od, strike, Call);
        BlackScholesPricer bspp(spot, sigma, r, od, strike, Put);

        const long size = (D2 - D1).days();
        const double h = od.getOptionYearsToMaturity()/size;

        //create random map of interest rates
        IRMap ir;
        static std::mt19937 u;
        double t = 0;
        for (unsigned long i = 0; i < size; ++i)
        {
            t += h;
            ir.insert(std::make_pair(t, static_cast<double>(u())/u.max()*0.1));
        }

        ShortRate ir_t(ir);
        const MoneyMarketAccount mmag(ir_t);
        F = spot*exp(ir_t.getAverageRate()*od.getOptionYearsToMaturity());

        BlackScholesPricer bspcg(spot, sigma, ir_t.getAverageRate(), od, strike, Call);
        BlackPricer bpcg(F, sigma, mmag, od, strike, Call);

        BOOST_TEST(bspc.optionPrice() == bpc.optionPrice());
        BOOST_TEST(bspp.optionPrice() == bpp.optionPrice());
        BOOST_TEST(bspcg.optionPrice() == bpcg.optionPrice());

    }

    BOOST_AUTO_TEST_CASE(dateToDoubleMappingTest_happyPath)
    {
        using namespace boost::gregorian;

        const double a = 0.1, b = 0.1, c = 0.1, d = 0.1;
        const date D1(2018, Apr, 26), D2(2019, May, 01);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);

        ParametricGeneralisedVolatility sigma_t(od, a, b, c, d);
        std::vector<double> valuesFromDouble, valuesFromDate;
        const double deltaT = od.getOptionYearsToMaturity()/od.getDaysToMaturity();

        double t = 0;
        date D = D1;

        for (unsigned long i = 0; i < od.getDaysToMaturity(); ++i)
        {
            t += deltaT;
            D += days(1);
            valuesFromDouble.push_back(sigma_t(t));
            valuesFromDate.push_back(sigma_t(D));
        }

        BOOST_TEST(valuesFromDate == valuesFromDouble, tt::per_element());

        //create random map of interest rates
        IRMap ir;
        std::map<date, double> irm;
        static std::mt19937 u;
        t = 0, D = D1;
        for (unsigned long i = 0; i < od.getDaysToMaturity(); ++i)
        {
            t += (i+1)*deltaT;
            D += days(i+1);
            const double value = static_cast<double>(u())/u.max()*0.1;
            ir.insert(std::make_pair(t, value));
            irm.insert(std::make_pair(D, value));
        }

        ShortRate ir_t(ir);
        ShortRate irm_t(irm, Act_Act);

        valuesFromDate.clear(), valuesFromDouble.clear();
        t = 0, D = D1;
        for (unsigned long i = 0; i < od.getDaysToMaturity(); ++i)
        {
            t += (i+1)*deltaT;
            D += days(i+1);
            valuesFromDate.push_back(irm_t(D));
            valuesFromDouble.push_back(ir_t(t));
        }

        BOOST_TEST(valuesFromDate == valuesFromDouble, tt::per_element());
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Monte_Carlo_pricing_tests)

    BOOST_AUTO_TEST_CASE(vanilla_eur_option)
    {
        using namespace boost::gregorian;

        const double spot = 100, strike = 50, r = 0.01, sigma = 0.25;
        const date D1(2018, Apr, 26), D2(2019, May, 01);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);

        PayOffCall poc(strike);
        PayOffPut pop(strike);
        Option cop(od, poc);
        Option popp(od, pop);
        MoneyMarketAccount mmaNum(r);

        BoxMuller rndGen;
        GeometricBM model(rndGen, r, sigma, poc.isExoticPayOff());
        //GeometricBM modelPut(rndGen, popp, r, sigma, poc.isExoticPayOff());

        const unsigned long nPaths = 5000;
        MonteCarloPricer pricerCall(model, cop, mmaNum, spot, nPaths);
        MonteCarloPricer pricerPut(model, popp, mmaNum, spot, nPaths);

        const double expectedCallPrice = 50.517944, expectedPutPrice = 0.013656;
        BOOST_TEST(std::abs(pricerCall.optionPrice() - expectedCallPrice) < 1.0);
        BOOST_TEST(std::abs(pricerPut.optionPrice() - expectedPutPrice) < 0.005);
    }

    BOOST_AUTO_TEST_CASE(exotic_eur_rangeAccrual_option)
    {
        using namespace boost::gregorian;

        const double spot = 105, upperSpot =  110, lowerSpot = 100, notional = 100;
        const double sigma = 0.25, r = 0.05;
        const date D1(2018, Apr, 26), D2(2019, Apr, 26);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);
        
        Range rgAccr(lowerSpot, upperSpot);

        PayOffRangeAccrual rangeAccrual(notional, rgAccr, od);
        Option op(od, rangeAccrual);
        MoneyMarketAccount mmaNum(r);

        const unsigned long nPaths = 10000;

        BeasleySpringerMoro rndGen;
        GeometricBM model(rndGen, r, sigma, rangeAccrual.isExoticPayOff());

        AntitheticSampling arndGen(rndGen, 2*nPaths);
        GeometricBM amodel(arndGen, r, sigma, rangeAccrual.isExoticPayOff());

        MonteCarloPricer pricer(model, op, mmaNum, spot, nPaths);
        MonteCarloPricer apricer(amodel, op, mmaNum, spot, nPaths*2);

        const double exactBSPrice = 25.5077;
        BOOST_TEST(std::abs(pricer.optionPrice() - exactBSPrice) < 0.5);
        BOOST_TEST(std::abs(apricer.optionPrice() - exactBSPrice) < 0.3);
        BOOST_TEST(apricer.stdError() < pricer.stdError());
    }

    BOOST_AUTO_TEST_CASE(barrier_vanilla_option)
    {
        using namespace boost::gregorian;

        const double spotDown = 170, spotUp = 120, sigma = 0.2, r = 0.05, strike = 100;
        const double barrier = 150;
        const date D1(2018, Apr, 26), D2(2019, Apr, 26);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);
        MoneyMarketAccount mmaNum(r);

        PayOffCall poc(strike);
        DownKnockOutBarrierEvent eventDown(barrier);
        DownKnockInBarrierEvent eventDownIn(barrier);
        UpKnockOutBarrierEvent eventUp(barrier);
        UpKnockInBarrierEvent eventUpIn(barrier);
        /*
        BarrierOption opd(od, poc, eventDown);
        BarrierOption opdi(od, poc, eventDownIn);
        BarrierOption opu(od, poc, eventUp);
        BarrierOption opui(od, poc, eventUpIn);*/

        Option opd(od, poc, eventDown);
        Option opdi(od, poc, eventDownIn);
        Option opu(od, poc, eventUp);
        Option opui(od, poc, eventUpIn);

        BeasleySpringerMoro rndGen;
        GeometricBM modelDown(rndGen, opd, r, sigma, true);
        GeometricBM modelDownIn(rndGen, opdi, r, sigma, true);
        GeometricBM modelUp(rndGen, opu, r, sigma, true);
        GeometricBM modelUpIn(rndGen, opui, r, sigma, true);
        const unsigned long nPaths = 10000;

        MonteCarloPricer pricer(modelDown, opd, mmaNum, spotDown, nPaths);
        const double downXCodePrice = 51.7627, upXCodePrice = 10.9423; //results from Xcode project

        double outOptionPrice = pricer.optionPrice();
        BOOST_TEST(std::abs(outOptionPrice - downXCodePrice ) < 0.2);

        pricer.setOption(opdi), pricer.setModel(modelDownIn);
        BlackScholesPricer bspd(spotDown, sigma, r, od, strike, Call);
        BOOST_TEST(std::abs(pricer.optionPrice() + outOptionPrice - bspd.optionPrice()) < 0.8); //KnockOut + KnockIn = KnockLess

        pricer.setOption(opu), pricer.setModel(modelUp), pricer.setSpot(spotUp);
        outOptionPrice = pricer.optionPrice();
        BOOST_TEST(std::abs(outOptionPrice - upXCodePrice ) < 0.2);

        pricer.setOption(opui), pricer.setModel(modelUpIn);
        BlackScholesPricer bspu(spotUp, sigma, r, od, strike, Call);
        BOOST_TEST(std::abs(pricer.optionPrice() + outOptionPrice - bspu.optionPrice()) < 0.4); //KnockOut + KnockIn = KnockLess
    }

    //more Monte Carlo unit tests here...
    //...

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Recombining_tree_pricers)
    BOOST_AUTO_TEST_CASE(Barrier_vanilla_option)
    {
        using namespace boost::gregorian;

        const double spotUp = 98, sigma = 0.2, r = 0.05, strike = 100;
        const double barrier = 130;
        const date D1(2018, Apr, 26), D2(2019, Apr, 26);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);
        MoneyMarketAccount mmaNum(r);

        PayOffCall poc(strike);
        UpKnockOutBarrierEvent eventUp(barrier);
        Option opt(od, poc, eventUp);

        const unsigned long N = 1000;
        JarrowRudd jr(sigma, r, od.getOptionYearsToMaturity(), N);
        BinomialTreePricer pricer(opt, jr, eventUp, spotUp, mmaNum);

        const double xCodePrice = 3.3164;
        BOOST_TEST(std::abs(pricer.optionPrice() - xCodePrice) < 1e-5);

        CoxRossRubinstein crr(sigma, od.getOptionYearsToMaturity(), 2*N);
        pricer.setMoveModel(crr);

        BOOST_TEST(std::abs(pricer.optionPrice() - 3.340478) < 1e-5);
    }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Interpolation_schemes)
    BOOST_AUTO_TEST_CASE(Natural_cubic_spline_fit)
    {
        std::map<double, double> f = {{0, exp(0)}, {1, exp(1)}, {2, exp(2)}, {3, exp(3)}};

        NaturalCubicSplineInterpolator ncsi;
        ncsi.fitSpline(f);

        std::vector<CSCoeffs> expectedCoeffs = {{1, 1.4659976141747231, 0 , 0.25228421428432202},
                        {2.7182818284590451, 2.2228502570276891, 0.75685264285296605, 1.6910713705909506},
                            {7.3890560989306504, 8.8097696545064732, 5.8300667546258174, -1.9433555848752724},
                                {20.085536923187668, 0, 0, 0}};

        for (unsigned int i = 0; i < 4; ++i)
        {
            BOOST_TEST(ncsi.getCoeffs().at(i).operator==(expectedCoeffs.at(i)));
        }
    }

    BOOST_AUTO_TEST_CASE(Natural_cubic_spline_interpolation)
    {
        std::map<double, double> f = {{0, exp(0)}, {1, exp(1)}, {2, exp(2)}, {3, exp(3)}};

        NaturalCubicSplineInterpolator ncsi;
        std::vector<double> queryPoints;

        double sum = -1, rightEndPoint = 4;
        const double dx = 0.2;
        while (sum < rightEndPoint + dx)
        {
            queryPoints.push_back(sum);
            sum += dx;
        }

        const std::map<double, double> act = ncsi.interpolatePoints(f, queryPoints);

        const std::string actual = actualPath + "Natural_cubic_spline_interpolation.txt";
        const std::string expected = expectedPath + "Natural_cubic_spline_interpolation_expected.txt";
        std::ofstream actualOut(actual);
        common::writeMap(act, actualOut, 5, false);

        std::ifstream expectedIn(expected);
        std::ifstream actualIn(actual);
        std::istream_iterator<char> expectedBeginIt(expectedIn), expectedEndIt;
        std::istream_iterator<char> actualBeginIt(actualIn), actualEndIt;
        BOOST_CHECK_EQUAL_COLLECTIONS(actualBeginIt, actualEndIt, expectedBeginIt, expectedEndIt);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IOUtils)
    BOOST_AUTO_TEST_CASE(IOUtils_writeMap)
    {

        std::pair<int, int> a = std::make_pair(1, 2); //y = 2x
        std::pair<int, int> b = std::make_pair(2, 4);
        std::pair<int, int> c = std::make_pair(3, 6);
        std::map<int, int> dMap = {a, b, c};

        std::ofstream out(actualPath + "IOUtils_writeMap.txt");
        const int precision = 0;
        writeMap(dMap, out, precision, true);

        std::ifstream inTestResult(actualPath + "IOUtils_writeMap.txt");
        std::ifstream inExpResult(expectedPath + "IOUtils_writeMap_expected.txt");

        std::istream_iterator<char> bTestResult(inTestResult), eTestResult;
        std::istream_iterator<char> bExpResult(inExpResult), eExpResult;

        BOOST_CHECK_EQUAL_COLLECTIONS(bTestResult, eTestResult, bExpResult, eExpResult);
    }

    BOOST_AUTO_TEST_CASE(IOUtils_readMap)
    {

        std::pair<double, double> a = std::make_pair(1, 2); //y = 2x
        std::pair<double, double> b = std::make_pair(2, 4);
        std::pair<double, double> c = std::make_pair(3, 6);
        std::pair<double, double> d = std::make_pair(4, 8);
        std::pair<double, double> e = std::make_pair(5, 10);
        std::map<double, double> dMap = {a, b, c, d, e};

        std::ifstream in(inputsPath + "IOUtils_readMap.txt");
        std::map<double, double> rMap;
        readMap(rMap, in, true);

        BOOST_CHECK(rMap == dMap);
    }

    BOOST_AUTO_TEST_CASE(IOUtils_writeMatrix)
    {
        std::vector<std::vector<int>> dMat = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};
        std::vector<std::string> labels = {"A", "B", "C", "D"};

        std::ofstream out(actualPath + "IOUtils_writeMatrix.txt");
        const int precision = 0;
        writeMatrix(dMat, out, precision, true, labels);

        std::ifstream inTestResult(actualPath + "IOUtils_writeMatrix.txt");
        std::ifstream inExpResult(expectedPath + "IOUtils_writeMatrix_expected.txt");

        std::istream_iterator<char> bTestResult(inTestResult), eTestResult;
        std::istream_iterator<char> bExpResult(inExpResult), eExpResult;

        BOOST_CHECK_EQUAL_COLLECTIONS(bTestResult, eTestResult, bExpResult, eExpResult);
    }

    BOOST_AUTO_TEST_CASE(IOUtils_readMatrix)
    {
        std::vector<std::vector<double>> dMat = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};


        std::ifstream in(inputsPath + "IOUtils_readMatrix.txt");
        std::vector<std::vector<double>> rMat(4);
        readMatrix(rMat, in, false);

        BOOST_CHECK(rMat == dMat);
    }
BOOST_AUTO_TEST_SUITE_END()




