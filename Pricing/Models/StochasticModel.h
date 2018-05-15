//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_STOCHASTICMODEL_H
#define QUANTLIB_STOCHASTICMODEL_H


#include "../PayOffSpecs/PayOff.h"
#include "../Pricing.h"
#include "../../Math/RandomNumbers/RandomNumberGenerator.h"
#include "../../Common/DateUtils/OptionDate.h"

class pricing::StochasticModel {
public:
    StochasticModel(const math::RandomNumberGenerator &rng);
    virtual PathMap SDE(double spot, const common::OptionDate& od) const = 0;

    virtual ~StochasticModel() {};

protected:
    std::unique_ptr<math::RandomNumberGenerator> m_rngPtr;
};


#endif //QUANTLIB_STOCHASTICMODEL_H
