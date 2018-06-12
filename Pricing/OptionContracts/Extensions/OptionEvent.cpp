//
// Created by Alberto Campi on 11/06/2018.
//

#include "OptionEvent.h"

pricing::OptionEvent::OptionEvent() : m_optionEventFlag(false), m_breakPathGenerationFlag(false) {}

bool pricing::OptionEvent::getOptionEventFlag() const
{
    return m_optionEventFlag;
}

bool pricing::OptionEvent::getBreakPathGenerationFlag() const
{
    return m_breakPathGenerationFlag;
}

void pricing::OptionEvent::resetAllFlags()
{
    m_optionEventFlag = false;
    m_breakPathGenerationFlag = false;
}