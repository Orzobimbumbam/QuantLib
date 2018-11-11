//
// Created by Alberto Campi on 03/08/2018.
//

#include "EarlyExerciseEvent.h"

//to be determined following future design. !!SUBJECT TO FURTHER CHANGES!!

pricing::EarlyExerciseEvent::EarlyExerciseEvent() : OptionEvent(), m_runningIntrinsicValue(0) {}

void pricing::EarlyExerciseEvent::actionAtOptionEvent() 
{
    return; 
}

double pricing::EarlyExerciseEvent::getPayOffAtOptionEvent(const PathMap &spot) const 
{
    return m_runningIntrinsicValue;
}

void pricing::EarlyExerciseEvent::resetAllFlags() 
{
    m_optionEventFlag = false;
    m_breakPathGenerationFlag = false;
}