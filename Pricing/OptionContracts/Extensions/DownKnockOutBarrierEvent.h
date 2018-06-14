//
// Created by Alberto Campi on 11/06/2018.
//

#ifndef QUANTLIB_DOWNKNOCKOUTBARRIEREVENT_H
#define QUANTLIB_DOWNKNOCKOUTBARRIEREVENT_H

#include "KnockOutBarrierEvent.h"

class pricing::DownKnockOutBarrierEvent : public pricing::KnockOutBarrierEvent {
public:
    explicit DownKnockOutBarrierEvent(double barrierLevel);
    
    bool optionEventHasOccurred(double spot) final;
    std::shared_ptr<pricing::OptionEvent> clone() const;

};


#endif //QUANTLIB_DOWNKNOCKOUTBARRIEREVENT_H
