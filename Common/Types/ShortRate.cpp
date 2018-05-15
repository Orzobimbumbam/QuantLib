//
// Created by Alberto Campi on 04/05/2018.
//

#include "ShortRate.h"

using namespace common;

ShortRate::ShortRate(const IRMap &shortRate, double h) : GeneralisedInterestRate(shortRate), m_h(h) {}

double ShortRate::operator()(double t) const
{
    return m_data.at(t);
}

double ShortRate::operator()(boost::gregorian::date t) const
{
    return m_dateDoubleMap.at(t);
}

long ShortRate::size() const
{
    return m_data.size();
}

IRMap ShortRate::get() const
{
    return m_data;
}

double ShortRate::getIntegrationStepSize() const {
    return m_h;
}
