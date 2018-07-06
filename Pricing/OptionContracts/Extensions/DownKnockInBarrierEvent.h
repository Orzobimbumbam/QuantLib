//
// Created by Alberto Campi on 06/07/2018.
//

#ifndef QUANTLIB_DOWNKNOCKINBARRIEREVENT_H
#define QUANTLIB_DOWNKNOCKINBARRIEREVENT_H

#include "KnockInBarrierEvent.h"

class pricing::DownKnockInBarrierEvent : public pricing::KnockInBarrierEvent {
public:
    explicit DownKnockInBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) final;
    std::shared_ptr<pricing::OptionEvent> clone() const;
};


#endif //QUANTLIB_DOWNKNOCKINBARRIEREVENT_H
