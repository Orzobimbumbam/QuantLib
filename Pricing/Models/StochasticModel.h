//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_STOCHASTICMODEL_H
#define QUANTLIB_STOCHASTICMODEL_H


#include "../PayOffSpecs/PayOff.h"
#include "../Pricing.h"

class pricing::StochasticModel {
public:
    virtual PathMap SDE(double spot, const common::OptionDate& od) const = 0;

    virtual ~StochasticModel() {};
private:

};


#endif //QUANTLIB_STOCHASTICMODEL_H
