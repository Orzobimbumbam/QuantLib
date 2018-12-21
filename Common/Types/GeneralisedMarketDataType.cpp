//
// Created by Alberto Campi on 02/05/2018.
//

#include "GeneralisedMarketDataType.h"

common::GeneralisedMarketDataType::GeneralisedMarketDataType(const std::map<double, double> &data) : m_data(data) {}
common::GeneralisedMarketDataType::GeneralisedMarketDataType(const std::map<boost::gregorian::date, double> &data,
                                                             DayCountConventionInUse dcc)
{
    _dateToDoubleMapper(data, dcc);
}

void common::GeneralisedMarketDataType::_dateToDoubleMapper(const std::map<boost::gregorian::date, double> &data,
DayCountConventionInUse dcc)
{
    using namespace boost::gregorian;

    const DayCountConventionHelper dcch(dcc);
    double t = 0;
    m_data.insert(std::make_pair(t, data.begin() -> second)), m_dateDoubleMap.insert(std::make_pair(data.begin() -> first, t));
    for (auto it = ++data.begin(); it != data.end(); ++it)
    {
        auto previous = it;
        --previous;
        t += dcch.getLengthInYears(previous -> first, it -> first);
        //t = dcch.getLengthInYears(data.begin() -> first, it -> first);
        m_data.insert(std::make_pair(t, it -> second));
        m_dateDoubleMap.insert(std::make_pair(it -> first, t));
    }
}
