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
    };

    BOOST_AUTO_TEST_CASE(NLSolver_HappyPath, *utf::tolerance(0.001))
    {
        const double yprecision = 1e-9;
        TestFixture fix;
        NLSolver<TestFixture, &TestFixture::shiftedParabola> s1(yprecision);
        NLSolver<TestFixture, &TestFixture::cubic, &TestFixture::derivativeCubic> s2(yprecision);

        BOOST_TEST(s1.solveByBisection(fix, 0, -0.5, 5) == (double)(1));
        BOOST_TEST(s2.solveByNR(fix, 0, 10) == (double)(0));
    }

    BOOST_AUTO_TEST_CASE(NumQuadrature_HappyPath, *utf::tolerance(0.001))
    {
        const double h = 0.01;
        TestFixture fix;
        NumQuadrature<TestFixture, &TestFixture::parabola> nq1(h);
        NumQuadrature<TestFixture, &TestFixture::cubic> nq2(h);


        const double a = -1, b = 1;
        const double exactParabolaIntegral = 2./3.;
        const double exactCubicIntegral = 0.0;

        const double midpointParabolaIntegral = nq1.integrateByMidPoint(fix, a, b);
        const double trapezoidParabolaIntegral = nq1.integrateByTrapezoid(fix, a, b);
        const double simpsonParabolaIntegral = nq1.integrateBySimpson(fix, a, b);
        const double midpointCubicIntegral = nq2.integrateByMidPoint(fix, a, b);
        const double trapezoidCubicIntegral = nq2.integrateByTrapezoid(fix, a, b);
        const double simpsonCubicIntegral = nq2.integrateBySimpson(fix, a, b);

        BOOST_TEST(midpointParabolaIntegral == exactParabolaIntegral);
        BOOST_TEST(trapezoidParabolaIntegral == exactParabolaIntegral);
        BOOST_TEST(simpsonParabolaIntegral == exactParabolaIntegral);
        //BOOST_TEST(std::abs(simpsonParabolaIntegral - exactParabolaIntegral) <
          //         std::abs(midpointParabolaIntegral - exactParabolaIntegral));
        //BOOST_TEST(std::abs(simpsonParabolaIntegral - exactParabolaIntegral) <
          //         std::abs(trapezoidParabolaIntegral - exactParabolaIntegral));

        BOOST_TEST(midpointCubicIntegral == exactCubicIntegral);
        BOOST_TEST(trapezoidCubicIntegral == exactCubicIntegral);
        BOOST_TEST(simpsonCubicIntegral == exactCubicIntegral);
        //BOOST_TEST(std::abs(simpsonCubicIntegral - exactCubicIntegral) <
          //         std::abs(midpointCubicIntegral - exactCubicIntegral));
        //BOOST_TEST(std::abs(simpsonCubicIntegral - exactCubicIntegral) <
          //         std::abs(trapezoidCubicIntegral - exactCubicIntegral));
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
        BOOST_CHECK_EQUAL(dchSimple.getAccrualPeriodInYears(D1, D2), expectedYearCount);
        BOOST_CHECK_EQUAL(dchActual.getAccrualPeriodInYears(D1, D2), expectedYearCount);
        BOOST_CHECK_EQUAL(dchSimple.getAccrualPeriodInYears(D1, D3), dchActual.getAccrualPeriodInYears(D1, D3));

        date D4(2020, Aug, 01);
        expectedYearCount = 1 + (250./365 + 213./366); //actual, 2020 is a leap year
        double expectedYearCountSimple = 828./365; //simple
        BOOST_CHECK_EQUAL(dchSimple.getAccrualPeriodInYears(D1, D4), expectedYearCountSimple);
        BOOST_CHECK_EQUAL(dchActual.getAccrualPeriodInYears(D1, D4), expectedYearCount);

        date D5(2021, Aug, 01);
        expectedYearCount = 153./366 + 212./365;
        BOOST_CHECK_EQUAL(dchActual.getAccrualPeriodInYears(D4, D5), expectedYearCount);

        date D6(2019, Jan, 01), D7(2021, Jan, 01);
        expectedYearCount = 2.;
        BOOST_CHECK_EQUAL(dchActual.getAccrualPeriodInYears(D6, D7), expectedYearCount);
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

        ShortRate ir_t(ir, h);
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

        ShortRate ir_t(ir, h);
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
            t += deltaT;
            D += days(1);
            const double value = static_cast<double>(u())/u.max()*0.1;
            ir.insert(std::make_pair(t, value));
            irm.insert(std::make_pair(D, value));
        }

        ShortRate ir_t(ir, deltaT);
        ShortRate irm_t(irm, Act_Act);

        valuesFromDate.clear(), valuesFromDouble.clear();
        t = 0, D = D1;
        for (unsigned long i = 0; i < od.getDaysToMaturity(); ++i)
        {
            t += deltaT;
            D += days(1);
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
        GeometricBM model(rndGen, cop, r, sigma, poc.isExoticPayOff());
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

        const double spot = 170, sigma = 0.2, r = 0.05, strike = 100;
        const double barrier = 150;
        const date D1(2018, Apr, 26), D2(2019, Apr, 26);
        const date D0 = D1;
        const OptionDate od(Act_Act, D2, D1, D0);
        MoneyMarketAccount mmaNum(r);

        PayOffCall poc(strike);
        DownKnockOutBarrierEvent event(barrier);
        DownOutBarrierOption op(od, poc, event);

        BeasleySpringerMoro rndGen;
        GeometricBM model(rndGen, op, r, sigma, true);
        const unsigned long nPaths = 10000;

        MonteCarloPricer pricer(model, op, mmaNum, spot, nPaths);
        const double UATprice = 51.7627; //result from Xcode project
        //BOOST_TEST(pricer.optionPrice() == 0);
        BOOST_TEST(std::abs(pricer.optionPrice() - UATprice ) < 0.2);
    }

BOOST_AUTO_TEST_SUITE_END()




