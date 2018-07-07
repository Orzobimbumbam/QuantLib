//
// Created by Alberto Campi on 07/07/2018.
//

#ifndef QUANTLIB_BARRIEREVENT_H
#define QUANTLIB_BARRIEREVENT_H


#include "OptionEvent.h"

class pricing::BarrierEvent : public pricing::OptionEvent {
public:
    explicit BarrierEvent(double barrierLevel);

    bool optionEventHasOccurred(double spot) override = 0;
    void actionAtOptionEvent() override = 0;
    double getPayOffAtOptionEvent(const PathMap &spot) const override = 0;
    void resetAllFlags() override = 0;

    std::shared_ptr<pricing::OptionEvent> clone() const override = 0;


protected:
    const double m_barrier;
};


#endif //QUANTLIB_BARRIEREVENT_H
