//
// Created by Alberto Campi on 30/04/2018.
//

#include "PayOffArithmeticAsianCall.h"

pricing::PayOffArithmeticAsianCall::PayOffArithmeticAsianCall(double strike, const LookAtDateArray& lookAtDates) :
        PayOff(true), m_strike(strike) , m_lookAtDates(lookAtDates) {}

double pricing::PayOffArithmeticAsianCall::payOff(const PathMap& dailySpot) const
{
    const long NLookAtDates = m_lookAtDates.size();
    if (NLookAtDates > 0)
    {
        double payOff = 0;
        for (const auto& it : m_lookAtDates)
            payOff += dailySpot.at(it);

        return payOff/NLookAtDates > m_strike ? payOff/NLookAtDates - m_strike : 0;
    }
    else
        throw std::overflow_error("pricing::PayOffArithmeticAsianCall::payOff : emtpy look-at-dates.");
}

std::unique_ptr<pricing::PayOff> pricing::PayOffArithmeticAsianCall::clone() const
{
    return std::make_unique<PayOffArithmeticAsianCall>(*this);
}