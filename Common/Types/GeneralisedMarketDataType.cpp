//
// Created by Alberto Campi on 02/05/2018.
//

#include "GeneralisedMarketDataType.h"

common::GeneralisedMarketDataType::GeneralisedMarketDataType(const std::map<double, double> &data) : m_data(data) {}
common::GeneralisedMarketDataType::GeneralisedMarketDataType(const std::map<boost::gregorian::date, double> &data,
                                                             DayCountConventionInUse dcc)
{
    dateToDoubleMapper(data, dcc);
}

void common::GeneralisedMarketDataType::dateToDoubleMapper(const std::map<boost::gregorian::date, double> &data,
DayCountConventionInUse dcc)
{
    using namespace boost::gregorian;

    const date D1 = data.begin() -> first, D2 = data.rbegin() -> first;
    const DayCountConventionHelper dcch(dcc);
    const double T = dcch.getAccrualPeriodInYears(D1, D2);
    const double deltaT = T/data.size();

    double t = 0;
    for (const auto& it : data)
    {
        t += deltaT;
        m_data.insert(std::make_pair(t, it.second));
        m_dateDoubleMap.insert(std::make_pair(it.first, t));
    }
    return;
}
