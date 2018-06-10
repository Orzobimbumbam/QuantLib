//
// Created by Alberto Campi on 25/04/2018.
//

#include "Option.h"

using namespace pricing;

Option::Option(const common::OptionDate &optionDate,
               const pricing::PayOff &optionPayOff) :
        m_optionPayOffType(optionPayOff.clone()), m_optionDate(optionDate), m_optionEventFlag(false) {}

Option::Option(const pricing::Option &sourceOption) : m_optionDate(sourceOption.m_optionDate),
                                                      m_optionPayOffType(sourceOption.m_optionPayOffType -> clone()),
                                                      m_optionEventFlag(sourceOption.m_optionEventFlag) {}
/*
pricing::Option Option::operator=(const pricing::Option &rhsOption)
{
    if (&rhsOption != this)
    {
        m_optionPayOffType.reset(); //delete internal raw pointer
        m_optionPayOffType = std::make_unique<pricing::PayOff>(rhsOption.m_optionPayOffType -> clone());

        m_optionDate = rhsOption.m_optionDate; //TODO: missing copy assignment in OptionDate class
    }
    return *this;
}*/

double Option::getOptionYearsToMaturity() const
{
    return m_optionDate.getOptionYearsToMaturity();
}

double Option::getOptionPayOff(const PathMap& spot) const
{
    if (!m_optionEventFlag)
        return m_optionPayOffType -> payOff(spot);
    else
        return getPayOffAtOptionEvent(spot);
}

common::OptionDate Option::getOptionDate() const
{
    return m_optionDate;
}

std::unique_ptr<pricing::Option> Option::clone() const
{
    return std::make_unique<pricing::Option>(*this);
}

bool Option::optionEventHasOccurred(double spot)
{
    return false; //no option event for European options
}

double Option::getPayOffAtOptionEvent(const PathMap& spot) const
{
    return 0.0; //dummy value, method is never called for this class
}