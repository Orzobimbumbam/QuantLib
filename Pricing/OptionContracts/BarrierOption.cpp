//
// Created by Alberto Campi on 12/06/2018.
//

#include "BarrierOption.h"
#include "Extensions/DownKnockOutBarrierEvent.h"

pricing::BarrierOption::BarrierOption(const common::OptionDate &optionDate,
                                                    const pricing::PayOff &optionPayOff,
                                                    const pricing::BarrierEvent& event) :
        Option(optionDate, optionPayOff, event) {}

pricing::BarrierOption::BarrierOption(const pricing::BarrierOption &sourceOption) :
        Option(sourceOption) {}

double pricing::BarrierOption::getOptionPayOff(const PathMap &spot) const
{
    if (m_optEventPtr -> getOptionEventFlag())
        return m_optEventPtr -> getPayOffAtOptionEvent(spot);
    else
        return m_optionPayOffType -> payOff(spot);
}

std::unique_ptr<pricing::Option> pricing::BarrierOption::clone() const
{
    return std::make_unique<pricing::BarrierOption>(*this);
}
/*
void pricing::BarrierOption::setBarrierEventType(const pricing::OptionEvent &event)
{
    m_optEventPtr = event.clone();
}*/