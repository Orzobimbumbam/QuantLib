//
// Created by Alberto Campi on 11/06/2018.
//

#ifndef QUANTLIB_DOWNKNOCKOUTBARRIEREVENT_H
#define QUANTLIB_DOWNKNOCKOUTBARRIEREVENT_H

#include "KnockOutBarrierEvent.h"

class pricing::DownKnockOutBarrierEvent : public pricing::KnockOutBarrierEvent {
public:
    DownKnockOutBarrierEvent(double barrierLevel);
    
    bool optionEventHasOccurred(double spot) final;

};


#endif //QUANTLIB_DOWNKNOCKOUTBARRIEREVENT_H
