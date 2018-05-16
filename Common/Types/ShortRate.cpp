//
// Created by Alberto Campi on 04/05/2018.
//

#include "ShortRate.h"

using namespace common;

ShortRate::ShortRate(const IRMap &shortRate, double h) : GeneralisedInterestRate(shortRate), m_h(h) {}

ShortRate::ShortRate(const std::map<boost::gregorian::date, double> &data, DayCountConventionInUse dcc) :
GeneralisedInterestRate(data, dcc), m_h(getH(data, dcc)) {}

double ShortRate::operator()(double t) const
{
    return m_data.at(t);
}

double ShortRate::operator()(boost::gregorian::date t) const
{
    return m_data.at(m_dateDoubleMap.at(t));
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

double ShortRate::getH(const std::map<boost::gregorian::date, double> &data, DayCountConventionInUse dcc) const
{
    using namespace boost::gregorian;

    const date D1 = data.begin() -> first - days(1), D2 = data.rbegin() -> first;
    const DayCountConventionHelper dcch(dcc);
    const double T = dcch.getAccrualPeriodInYears(D1, D2);
    return T/(data.size());
}