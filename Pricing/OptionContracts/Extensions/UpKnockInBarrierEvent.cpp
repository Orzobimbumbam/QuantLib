//
// Created by Alberto Campi on 05/07/2018.
//

#include "UpKnockInBarrierEvent.h"

pricing::UpKnockInBarrierEvent::UpKnockInBarrierEvent(double barrierLevel) : KnockInBarrierEvent(barrierLevel) {}

bool pricing::UpKnockInBarrierEvent::optionEventHasOccurred(double spot)
{
    if (spot >= m_barrier)
        m_optionEventFlag = false;

    return m_optionEventFlag;
}

std::shared_ptr<pricing::OptionEvent> pricing::UpKnockInBarrierEvent::clone() const
{
    return std::make_shared<pricing::UpKnockInBarrierEvent>(*this);
}
