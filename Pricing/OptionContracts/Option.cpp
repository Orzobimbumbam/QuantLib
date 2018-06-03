//
// Created by Alberto Campi on 25/04/2018.
//

#include "Option.h"

using namespace pricing;

Option::Option(const common::OptionDate &optionDate,
               const pricing::PayOff &optionPayOff) :
        m_optionPayOffType(optionPayOff.clone()), m_optionDate(optionDate) {}

Option::Option(const pricing::Option &sourceOption) : m_optionDate(sourceOption.m_optionDate),
                                                      m_optionPayOffType(sourceOption.m_optionPayOffType -> clone()) {}
/*
pricing::Option Option::operator=(const pricing::Option &rhsOption)
{
    if (&rhsOption != this)
    {
        m_optionPayOffType.reset(); //delete internal raw pointer
        m_optionPayOffType = std::make_unique<pricing::PayOff>(rhsOption.m_optionPayOffType -> clone());

        m_optionDate = rhsOption.m_optionDate;
    }
    return *this;
}*/

double Option::getOptionYearsToMaturity() const
{
    return m_optionDate.getOptionYearsToMaturity();
}

double Option::getOptionPayOff(const PathMap& spot) const
{
    return m_optionPayOffType -> payOff(spot);
}

common::OptionDate Option::getOptionDate() const
{
    return m_optionDate;
}