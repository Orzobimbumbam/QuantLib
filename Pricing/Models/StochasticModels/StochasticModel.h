//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_STOCHASTICMODEL_H
#define QUANTLIB_STOCHASTICMODEL_H


#include "../../PayOffSpecs/PayOff.h"
#include "../../Pricing.h"
#include "../../../Math/RandomNumbers/RandomNumberGenerator.h"
#include "../../../Common/DateUtils/OptionDate.h"
#include "../../OptionContracts/Extensions/OptionEvent.h"
#include "../../OptionContracts/Option.h"

class pricing::StochasticModel {
public:
    StochasticModel(const math::RandomNumberGenerator &rng);
    StochasticModel(const math::RandomNumberGenerator &rng, const pricing::Option &optionStyle);
    StochasticModel(const pricing::StochasticModel& sourceModel);
    
    virtual PathMap SDE(double spot, const common::OptionDate& od) const = 0;
    virtual std::unique_ptr<pricing::StochasticModel> clone() const = 0;

    virtual ~StochasticModel() = default;

protected:
    const std::unique_ptr<math::RandomNumberGenerator> m_rngPtr;
    const std::shared_ptr<pricing::OptionEvent> m_optEventPtr;
    static const unsigned long m_deltaT;

    void resetOptionEventFlags() const;
};


#endif //QUANTLIB_STOCHASTICMODEL_H
