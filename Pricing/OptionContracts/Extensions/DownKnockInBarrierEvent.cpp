//
// Created by Alberto Campi on 06/07/2018.
//

#include "DownKnockInBarrierEvent.h"

pricing::DownKnockInBarrierEvent::DownKnockInBarrierEvent(double barrierLevel) : KnockInBarrierEvent(barrierLevel) {}

bool pricing::DownKnockInBarrierEvent::optionEventHasOccurred(double spot)
{
    if (spot <= m_barrier)
    {
        m_optionEventFlag = false;
    }

    return m_optionEventFlag;
}

std::shared_ptr<pricing::OptionEvent> pricing::DownKnockInBarrierEvent::clone() const
{
    return std::make_shared<pricing::DownKnockInBarrierEvent>(*this);
}