//
// Created by Alberto Campi on 05/07/2018.
//

#include "KnockInBarrierEvent.h"

pricing::KnockInBarrierEvent::KnockInBarrierEvent(double barrierLevel) : BarrierEvent(barrierLevel)
{
    m_optionEventFlag = true;
}

void pricing::KnockInBarrierEvent::actionAtOptionEvent()
{
    return;
}

double pricing::KnockInBarrierEvent::getPayOffAtOptionEvent(const PathMap &spot) const
{
    return 0.0; //return zero if barrier hasn't been touched, flag is set to true by default.
}

void pricing::KnockInBarrierEvent::resetAllFlags()
{
    m_optionEventFlag = true;
    m_breakPathGenerationFlag = false;
}