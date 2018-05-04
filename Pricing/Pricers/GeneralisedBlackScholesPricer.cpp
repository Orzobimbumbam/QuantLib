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
                                                             PutCallFlag pcf) :

BlackScholesPricer(spot, getRMSSquaredVolatility(squaredVol, dates.getOptionYearsToMaturity()), getAverageRate(interestRate, dates.getOptionYearsToMaturity()),
dates, strike, pcf) {}

double GeneralisedBlackScholesPricer::getRMSSquaredVolatility(const GeneralisedMarketDataType &squaredVol, double ytm) const
{
    const double stepSize = ytm/squaredVol.size();
    NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    const double T = squaredVol.get().rbegin() -> first - stepSize;

    return sqrt(1./T*integrator.integrateBySimpson(squaredVol, stepSize, squaredVol.get().rbegin() -> first));
}

double GeneralisedBlackScholesPricer::getAverageRate(const GeneralisedMarketDataType &interestRate, double ytm) const
{
    const double stepSize = ytm/interestRate.size();
    NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    const double T = interestRate.get().rbegin() -> first - stepSize;

    return 1./T*integrator.integrateBySimpson(interestRate, stepSize, interestRate.get().rbegin() -> first);
}

double GeneralisedBlackScholesPricer::getAverageRate() const
{
    return m_r;
}

double GeneralisedBlackScholesPricer::getRMSSquaredVolatility() const
{
    return m_vol;
}