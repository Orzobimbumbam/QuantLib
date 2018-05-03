//
// Created by Alberto Campi on 14/04/2018.
//

#include "PayOffCall.h"
using namespace pricing;

PayOffCall::PayOffCall(double strike): PayOff(false), m_strike(strike) {}
PayOffCall::PayOffCall(double strike, bool isPathDependent): PayOff(isPathDependent), m_strike(strike) {}

double PayOffCall::payOff(const PathMap& spot) const
{
    if (!spot.empty())
        return spot.rbegin() -> second > m_strike ? spot.rbegin() -> second - m_strike : 0; //array being passed is one-dimensional
    else
        throw std::runtime_error("pricing::PayOffCall::PayOff : payoff cannot be evaluated on an empty spot path.");
}

std::unique_ptr<PayOff> PayOffCall::clone() const
{
    return std::make_unique<PayOffCall>(*this);
}