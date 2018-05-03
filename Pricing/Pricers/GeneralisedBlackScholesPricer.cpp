//
// Created by Alberto Campi on 02/05/2018.
//

#include "GeneralisedBlackScholesPricer.h"
#include "../../Math/math.h"

using namespace pricing;
using namespace math;


GeneralisedBlackScholesPricer::GeneralisedBlackScholesPricer(double spot, const GeneralisedVolatility& squaredVol,
                                                             const GeneralisedInterestRate& interestRate,
                                                             const common::OptionDate &dates, double strike,
                                                             PutCallFlag pcf, double h) :

BlackScholesPricer(spot, getRMSVol(squaredVol, dates.getOptionYearsToMaturity()), getAvgRate(interestRate, dates.getOptionYearsToMaturity()),
dates, strike, pcf) {}

double GeneralisedBlackScholesPricer::getRMSVol(const GeneralisedMarketDataType &squaredVol, double ytm) const
{
    const double stepSize = ytm/squaredVol.size();
    NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    return sqrt(1./ytm*integrator.integrateByMidPoint(squaredVol, 0, ytm));
}

double GeneralisedBlackScholesPricer::getAvgRate(const GeneralisedMarketDataType &interestRate, double ytm) const
{
    const double stepSize = ytm/interestRate.size();
    NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    return 1./ytm*integrator.integrateByMidPoint(interestRate, 0, ytm);
}
