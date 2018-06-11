//
// Created by Alberto Campi on 11/06/2018.
//

#include "DownKnockOutBarrierEvent.h"

pricing::DownKnockOutBarrierEvent::DownKnockOutBarrierEvent(double barrierLevel) : KnockOutBarrierEvent(barrierLevel) {}

bool pricing::DownKnockOutBarrierEvent::optionEventHasOccurred(double spot)
{
    if (spot >= m_barrier)
    {
        m_optionEventFlag = true;
        m_breakPathGenerationFlag = true;
    }

    return m_optionEventFlag;
}