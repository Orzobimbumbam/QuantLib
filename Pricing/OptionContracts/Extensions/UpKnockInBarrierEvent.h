//
// Created by Alberto Campi on 05/07/2018.
//

#ifndef QUANTLIB_UPKNOCKINBARRIEREVENT_H
#define QUANTLIB_UPKNOCKINBARRIEREVENT_H

#include "KnockInBarrierEvent.h"


class pricing::UpKnockInBarrierEvent : public pricing::KnockInBarrierEvent {
public:
    explicit UpKnockInBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) final;

    std::shared_ptr<pricing::OptionEvent> clone() const override;
};


#endif //QUANTLIB_UPKNOCKINBARRIEREVENT_H
