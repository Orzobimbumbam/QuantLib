//
// Created by Alberto Campi on 12/06/2018.
//

#include "DownOutBarrierOption.h"
#include "Extensions/DownKnockOutBarrierEvent.h"

pricing::DownOutBarrierOption::DownOutBarrierOption(const common::OptionDate &optionDate,
                                                    const pricing::PayOff &optionPayOff,
                                                    const pricing::DownKnockOutBarrierEvent& event) :
        Option(optionDate, optionPayOff) { m_optEventPtr = std::make_shared<pricing::DownKnockOutBarrierEvent>(event); }

pricing::DownOutBarrierOption::DownOutBarrierOption(const pricing::DownOutBarrierOption &sourceOption) :
        Option(sourceOption) { m_optEventPtr = sourceOption.m_optEventPtr; }

double pricing::DownOutBarrierOption::getOptionPayOff(const PathMap &spot) const
{
    if (m_optEventPtr -> getOptionEventFlag())
        return m_optEventPtr -> getPayOffAtOptionEvent(spot);
    else
        return m_optionPayOffType -> payOff(spot);
}

std::unique_ptr<pricing::Option> pricing::DownOutBarrierOption::clone() const
{
    return std::make_unique<pricing::DownOutBarrierOption>(*this);
}