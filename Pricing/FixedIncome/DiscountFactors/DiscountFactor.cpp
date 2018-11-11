//
// Created by Alberto Campi on 11/11/2018.
//

#include <cmath>
#include "DiscountFactor.h"

double pricing::DiscountFactorLIBORRate::getDiscountFactor(double accrualPeriodInYears, double annualisedRate) const
{
    return 1/(1 + accrualPeriodInYears*annualisedRate);
}

std::unique_ptr<pricing::DiscountFactor> pricing::DiscountFactorLIBORRate::clone() const
{
    return std::make_unique<pricing::DiscountFactorLIBORRate>(*this);
}



pricing::DiscountFactorCompoundedRate::DiscountFactorCompoundedRate(long numberOfAnnualCashFlows) :
        m_numberOfAnnualCashFlows(numberOfAnnualCashFlows) {}

double pricing::DiscountFactorCompoundedRate::getDiscountFactor(double tenorInYears, double annualisedRate) const
{
    const double compoundingRate = annualisedRate/m_numberOfAnnualCashFlows;
    auto cashFlowNumber = static_cast<long>(tenorInYears*m_numberOfAnnualCashFlows);
    return 1/pow(1 + compoundingRate, cashFlowNumber);
}

std::unique_ptr<pricing::DiscountFactor> pricing::DiscountFactorCompoundedRate::clone() const
{
    return std::make_unique<pricing::DiscountFactorCompoundedRate>(*this);
}



double pricing::DiscountFactorContinuouslyCompoundedRate::getDiscountFactor(double tenorInYears,
                                                                            double annualisedRate) const
{
    return exp(-annualisedRate*tenorInYears);
}

std::unique_ptr<pricing::DiscountFactor> pricing::DiscountFactorContinuouslyCompoundedRate::clone() const
{
    return std::make_unique<pricing::DiscountFactorContinuouslyCompoundedRate>(*this);
}