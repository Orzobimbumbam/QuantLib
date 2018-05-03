//
// Created by Alberto Campi on 15/04/2018.
//

#include "StatOneDim.h"
#include <cmath>

math::StatOneDim::StatOneDim() : Stat(1), m_sumOfRV(0), m_sumOfSquaredRV(0) {}

void math::StatOneDim::add(double x)
{
    m_sumOfRV += x;
    m_sumOfSquaredRV += x*x;
    ++m_counter;
}

double math::StatOneDim::mean() const
{
    checkCounter();
    return m_sumOfRV/m_counter;
}

double math::StatOneDim::variance() const
{
    checkCounter();
    return (m_sumOfSquaredRV - m_sumOfRV*m_sumOfRV/m_counter)/m_counter;
}

double math::StatOneDim::stdDev() const
{
    return sqrt(variance());
}

double math::StatOneDim::stdError() const
{
    return stdDev()/sqrt(m_counter);
}