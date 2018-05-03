//
// Created by Alberto Campi on 25/04/2018.
//

#include "Option.h"

using namespace pricing;

Option::Option(const common::OptionDate &optionDate,
               const pricing::PayOff &optionPayOff) :
        m_optionPayOffType(optionPayOff.clone()), m_optionDate(optionDate) {}

double Option::getOptionYearsToMaturity() const
{
    return m_optionDate.getOptionYearsToMaturity();
}

double Option::getOptionPayOff(const PathMap& spot) const
{
    return m_optionPayOffType -> payOff(spot);
}
