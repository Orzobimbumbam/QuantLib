//
// Created by Alberto Campi on 05/07/2018.
//

#ifndef QUANTLIB_KNOCKINBARRIEREVENT_H
#define QUANTLIB_KNOCKINBARRIEREVENT_H

#include "BarrierEvent.h"


class pricing::KnockInBarrierEvent : public pricing::BarrierEvent {
public:
    explicit KnockInBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) override = 0;
    void actionAtOptionEvent() override;
    double getPayOffAtOptionEvent(const PathMap &spot) const final;
    void resetAllFlags() final;

    std::shared_ptr<pricing::OptionEvent> clone() const override = 0;


protected:

};


#endif //QUANTLIB_KNOCKINBARRIEREVENT_H
