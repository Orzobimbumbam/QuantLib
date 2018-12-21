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
        BlackScholesPricer(spot, squaredVol.getRMSSquaredVolatility(), interestRate.getAverageRate(), dates, strike, pcf)
{
    //validate dates and day-count convention in use
    const double squaredVolT = squaredVol.get().rbegin() -> first - squaredVol.get().begin() -> first;
    const double interestRateT = interestRate.get().rbegin() -> first - interestRate.get().begin() -> first;

    if (dates.getOptionYearsToMaturity() == squaredVolT == interestRateT)
        throw std::out_of_range("GeneralisedBlackScholesPricer::GeneralisedBlackScholesPricer : inconsistent date range");
}

//Dividend yield is implicitly assumed to be 0. This can be changed by implementing getAverageYield logic

double GeneralisedBlackScholesPricer::getAverageRate() const
{
    return m_r;
}

double GeneralisedBlackScholesPricer::getRMSSquaredVolatility() const
{
    return m_vol;
}
