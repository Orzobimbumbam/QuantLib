//
// Created by Alberto Campi on 13/06/2018.
//

#include "UpKnockOutBarrierEvent.h"

pricing::UpKnockOutBarrierEvent::UpKnockOutBarrierEvent(double barrierLevel) : KnockOutBarrierEvent(barrierLevel) {}

bool pricing::UpKnockOutBarrierEvent::optionEventHasOccurred(double spot)
{
    if (spot >= m_barrier)
        m_optionEventFlag = true;

    return m_optionEventFlag;
}

std::shared_ptr<pricing::OptionEvent> pricing::UpKnockOutBarrierEvent::clone() const
{
    return std::make_shared<pricing::UpKnockOutBarrierEvent>(*this);
}
