//
// Created by Alberto Campi on 14/04/2018.
//

#include "PayOffPut.h"
using namespace pricing;

PayOffPut::PayOffPut(double strike): PayOff(false), m_strike(strike) {}
PayOffPut::PayOffPut(double strike, bool isPathDependent): PayOff(isPathDependent), m_strike(strike) {}

double PayOffPut::payOff(const PathMap& spot) const
{
    if (!spot.empty())
        return spot.rbegin() -> second < m_strike ? m_strike - spot.rbegin() -> second : 0;
    else
        throw std::runtime_error("pricing::PayOffCall::PayOff : payoff cannot be evaluated on an empty spot path.");
}

std::unique_ptr<PayOff> PayOffPut::clone() const
{
    return std::make_unique<PayOffPut>(*this);
}