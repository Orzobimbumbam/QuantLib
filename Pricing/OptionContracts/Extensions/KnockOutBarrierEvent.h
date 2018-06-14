//
// Created by Alberto Campi on 11/06/2018.
//

#ifndef QUANTLIB_KNOCKOUTBARRIEREVENT_H
#define QUANTLIB_KNOCKOUTBARRIEREVENT_H

#include "OptionEvent.h"


class pricing::KnockOutBarrierEvent : public pricing::OptionEvent {
public:
    explicit KnockOutBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) override = 0;
    void actionAtOptionEvent() override;
    double getPayOffAtOptionEvent(const PathMap &spot) const final;

    std::shared_ptr<pricing::OptionEvent> clone() const override = 0;


protected:
    const double m_barrier;

private:
    //KnockOutBarrierEvent() = default;
};


#endif //QUANTLIB_KNOCKOUTBARRIEREVENT_H
