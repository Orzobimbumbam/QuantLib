//
// Created by Alberto Campi on 05/06/2018.
//

#include <cmath>
#include "Range.h"

common::Range::Range(double lower, double upper) : m_lower(lower), m_upper(upper), m_meshSize(0) {}
common::Range::Range(double lower, double upper, double meshSize) : m_lower(lower), m_upper(upper), m_meshSize(0)
{
    partition();
}

double common::Range::getLower() const
{
    return m_lower;
}

double common::Range::getUpper() const
{
    return m_upper;
}

double common::Range::getMeshSize() const
{
    return m_meshSize;
}

Partition common::Range::getPartition() const
{
    return m_partition;
}

void common::Range::setLower(double lower)
{
    m_lower = lower;
}

void common::Range::setUpper(double upper)
{
    m_lower = upper;
}

void common::Range::partition()
{
    const unsigned long N = std::abs(m_upper - m_lower)/m_meshSize;
    double movingMesh = m_lower;
    m_partition.insert(movingMesh);

    for (unsigned long i = 0; i < N; ++i)
    {
        movingMesh += m_meshSize;
        m_partition.insert(movingMesh);
    }

    return;
}