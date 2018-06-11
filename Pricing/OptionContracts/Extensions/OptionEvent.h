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
    virtual bool optionEventHasOccurred(double spot) = 0;
    virtual void actionAtOptionEvent() const = 0;
    virtual double getPayOffAtOptionEvent(const PathMap& spot) const = 0;

    bool getOptionEventFlag() const;
    bool getBreakPathGenerationFlag() const;

    virtual ~OptionEvent() = default;

protected:
    bool m_optionEventFlag;
    bool m_breakPathGenerationFlag;
};


#endif //QUANTLIB_OPTIONEVENT_H
