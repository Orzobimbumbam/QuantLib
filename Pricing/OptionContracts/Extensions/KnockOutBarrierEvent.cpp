//
// Created by Alberto Campi on 11/06/2018.
//

#include "KnockOutBarrierEvent.h"

pricing::KnockOutBarrierEvent::KnockOutBarrierEvent(double barrierLevel) : m_barrier(barrierLevel) {}

void pricing::KnockOutBarrierEvent::actionAtOptionEvent()
{
    m_breakPathGenerationFlag = true;
}

double pricing::KnockOutBarrierEvent::getPayOffAtOptionEvent(const PathMap &spot) const
{
    return 0.0;
}
