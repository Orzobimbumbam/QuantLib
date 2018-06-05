//
// Created by Alberto Campi on 04/06/2018.
//

#include "PayOffRangeAccrual.h"

pricing::PayOffRangeAccrual::PayOffRangeAccrual(double notional, double upperSpot, double lowerSpot, const common::OptionDate &dates) :
        PayOff(true), m_notional(notional), m_od(dates), m_upperSpot(upperSpot), m_lowerSpot(lowerSpot) {}

double pricing::PayOffRangeAccrual::payOff(const PathMap &spot) const
{
    unsigned long D = m_od.getDaysToMaturity(); //TODO: should get number of business days
    //unsigned long D = 252;
    unsigned long d = 0;

    for (const auto& itSpot : spot)
        if (itSpot.second >= m_lowerSpot && itSpot.second <= m_upperSpot)
            ++d;
    const double ratio = static_cast<double>(d)/D;
    return m_notional*ratio;
}

std::unique_ptr<pricing::PayOff> pricing::PayOffRangeAccrual::clone() const
{
    return std::make_unique<pricing::PayOffRangeAccrual>(*this);
}
