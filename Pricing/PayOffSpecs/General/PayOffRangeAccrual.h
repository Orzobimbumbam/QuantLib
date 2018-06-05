//
// Created by Alberto Campi on 04/06/2018.
//

#ifndef QUANTLIB_PAYOFFRANGEACCRUAL_H
#define QUANTLIB_PAYOFFRANGEACCRUAL_H


#include "../PayOff.h"
#include "../../Pricing.h"

class pricing::PayOffRangeAccrual : public pricing::PayOff {
public:
    PayOffRangeAccrual(double notional, double upperSpot, double lowerSpot, const common::OptionDate& dates);
    //PayOffRangeAccrual(double notional, double upperSpot, double lowerSpot, const common::OptionDate& dates,
                       //unsigned long tradingDays);

    double payOff(const PathMap &spot) const override;

    std::unique_ptr<PayOff> clone() const override;

private:
    const double m_notional;
    const common::OptionDate m_od;
    const double m_upperSpot, m_lowerSpot;
};


#endif //QUANTLIB_PAYOFFRANGEACCRUAL_H
