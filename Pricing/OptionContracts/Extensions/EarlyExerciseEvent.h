//
// Created by Alberto Campi on 03/08/2018.
//

#ifndef QUANTLIB_EARLYEXERCISEEVENT_H
#define QUANTLIB_EARLYEXERCISEEVENT_H

#include "OptionEvent.h"


class pricing::EarlyExerciseEvent : public pricing::OptionEvent {
public:
    EarlyExerciseEvent();

    bool optionEventHasOccurred(double intrinsicValue) override = 0;
    void actionAtOptionEvent() override;
    double getPayOffAtOptionEvent(const PathMap& spot) const override;

    void resetAllFlags() override;

    virtual std::shared_ptr<pricing::OptionEvent> clone() const override = 0;

protected:
    double m_runningIntrinsicValue;

};


#endif //QUANTLIB_EARLYEXERCISEEVENT_H
