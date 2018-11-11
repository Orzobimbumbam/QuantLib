//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_DISCOUNTFACTOR_H
#define QUANTLIB_DISCOUNTFACTOR_H

#include "../../pricing.h"
#include <memory>


class pricing::DiscountFactor {
public:
    virtual double getDiscountFactor(double tenor, double rate) const = 0;
    virtual std::unique_ptr<pricing::DiscountFactor> clone() const = 0;

    virtual ~DiscountFactor() = default;

private:

};

class pricing::DiscountFactorLIBORRate : public pricing::DiscountFactor
{
public:
    double getDiscountFactor(double accrualPeriodInYears, double annualisedRate) const override;
    std::unique_ptr<pricing::DiscountFactor> clone() const override;

private:

};

class pricing::DiscountFactorCompoundedRate : public pricing::DiscountFactor
{
public:
    explicit DiscountFactorCompoundedRate(long numberOfAnnualCashFlows);

    double getDiscountFactor(double tenorInYears, double annualisedRate) const override;
    std::unique_ptr<pricing::DiscountFactor> clone() const override;

private:
    const long m_numberOfAnnualCashFlows;
};

class pricing::DiscountFactorContinuouslyCompoundedRate : public pricing::DiscountFactor
{
public:
    double getDiscountFactor(double tenorInYears, double annualisedRate) const override;
    std::unique_ptr<pricing::DiscountFactor> clone() const override;

private:

};

#endif //QUANTLIB_DISCOUNTFACTOR_H
