//
// Created by Alberto Campi on 13/06/2018.
//

#ifndef QUANTLIB_UPKNOCKOUTBARRIEREVENT_H
#define QUANTLIB_UPKNOCKOUTBARRIEREVENT_H

#include "KnockOutBarrierEvent.h"

class pricing::UpKnockOutBarrierEvent : public pricing::KnockOutBarrierEvent {
public:
    explicit UpKnockOutBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) final;

    std::shared_ptr<pricing::OptionEvent> clone() const override;

};


#endif //QUANTLIB_UPKNOCKOUTBARRIEREVENT_H
