//
// Created by Alberto Campi on 11/06/2018.
//

#ifndef QUANTLIB_OPTIONEVENT_H
#define QUANTLIB_OPTIONEVENT_H


#include "../../PayOffSpecs/PayOff.h"
#include "../../Pricing.h"

class pricing::OptionEvent {
public:
    OptionEvent();
    virtual bool optionEventHasOccurred(double triggerValue) = 0;
    virtual void actionAtOptionEvent() = 0;
    virtual double getPayOffAtOptionEvent(const PathMap& spot) const = 0;

    bool getOptionEventFlag() const;
    bool getBreakPathGenerationFlag() const; //relevant for Monte Carlo only
    virtual void resetAllFlags() = 0;

    virtual std::shared_ptr<pricing::OptionEvent> clone() const = 0;

    virtual ~OptionEvent() = default;

protected:
    bool m_optionEventFlag;
    bool m_breakPathGenerationFlag;
};


#endif //QUANTLIB_OPTIONEVENT_H
