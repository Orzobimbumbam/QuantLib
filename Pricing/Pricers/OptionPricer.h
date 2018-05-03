//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_OPTIONPRICER_H
#define QUANTLIB_OPTIONPRICER_H

#include "../Pricing.h"

class pricing::OptionPricer
{
public:
    virtual double optionPrice() const = 0;

    virtual ~OptionPricer() {};
};

#endif //QUANTLIB_OPTIONPRICER_H
