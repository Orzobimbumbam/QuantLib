//
// Created by Alberto Campi on 11/06/2018.
//

#ifndef QUANTLIB_KNOCKOUTBARRIEREVENT_H
#define QUANTLIB_KNOCKOUTBARRIEREVENT_H

#include "BarrierEvent.h"


class pricing::KnockOutBarrierEvent : public pricing::BarrierEvent {
public:
    explicit KnockOutBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) override = 0;
    void actionAtOptionEvent() override;
    double getPayOffAtOptionEvent(const PathMap &spot) const final;
    void resetAllFlags() final;

    std::shared_ptr<pricing::OptionEvent> clone() const override = 0;


protected:

};


#endif //QUANTLIB_KNOCKOUTBARRIEREVENT_H
