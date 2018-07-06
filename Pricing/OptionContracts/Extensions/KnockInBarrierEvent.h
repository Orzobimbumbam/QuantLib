//
// Created by Alberto Campi on 05/07/2018.
//

#ifndef QUANTLIB_KNOCKINBARRIEREVENT_H
#define QUANTLIB_KNOCKINBARRIEREVENT_H

#include "OptionEvent.h"


class pricing::KnockInBarrierEvent : public pricing::OptionEvent {
public:
    explicit KnockInBarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) override = 0;
    void actionAtOptionEvent() override;
    double getPayOffAtOptionEvent(const PathMap &spot) const final;
    void resetAllFlags() final;

    std::shared_ptr<pricing::OptionEvent> clone() const override = 0;


protected:
    const double m_barrier;

private:
};


#endif //QUANTLIB_KNOCKINBARRIEREVENT_H
