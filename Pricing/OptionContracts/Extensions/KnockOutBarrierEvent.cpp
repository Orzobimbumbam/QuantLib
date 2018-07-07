//
// Created by Alberto Campi on 11/06/2018.
//

#include "KnockOutBarrierEvent.h"

pricing::KnockOutBarrierEvent::KnockOutBarrierEvent(double barrierLevel) : BarrierEvent(barrierLevel) {}

void pricing::KnockOutBarrierEvent::actionAtOptionEvent()
{
    m_breakPathGenerationFlag = true;
}

double pricing::KnockOutBarrierEvent::getPayOffAtOptionEvent(const PathMap &spot) const
{
    return 0.0;
}

void pricing::KnockOutBarrierEvent::resetAllFlags()
{
    m_optionEventFlag = false;
    m_breakPathGenerationFlag = false;
}