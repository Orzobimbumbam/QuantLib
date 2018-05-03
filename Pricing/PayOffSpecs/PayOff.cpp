//
// Created by Alberto Campi on 14/04/2018.
//

#include "PayOff.h"
using namespace pricing;

PayOff::PayOff(bool isPathDependent) : m_isPathDependent(isPathDependent) {}
PayOff::~PayOff() {}

double PayOff::operator()(const PathMap& spot) const
{
    return payOff(spot);
}

bool PayOff::isExoticPayOff() const
{
    return m_isPathDependent;
}