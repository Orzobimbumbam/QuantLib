//
// Created by Alberto Campi on 14/04/2018.
//

#ifndef QUANTLIB_PAYOFF_H
#define QUANTLIB_PAYOFF_H

#include <memory>
#include <vector>
#include "../Pricing.h"
#include "../../Common/DateUtils/OptionDate.h"

typedef std::map<boost::gregorian::date, double> PathMap;

class pricing::PayOff
{
public:
    virtual double payOff(const PathMap& spot) const = 0; //generalise payoff for exotics
    virtual double operator()(const PathMap& spot) const;
    virtual bool isExoticPayOff() const;
    virtual std::unique_ptr<PayOff> clone() const = 0;

    virtual ~PayOff();

protected:
    explicit PayOff(bool isPathDependent);
    const bool m_isPathDependent;
};


#endif //QUANTLIB_PAYOFF_H
