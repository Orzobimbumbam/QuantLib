//
// Created by Alberto Campi on 14/04/2018.
//

#include "Stat.h"
#include <cmath>


void math::Stat::checkCounter() const
{
    if (m_counter == 0)
        throw std::overflow_error("Stat::checkCounter : Divide by zero exception");
}

math::Stat::Stat(unsigned int dimension) : m_dim(dimension), m_counter(0), m_sumOfRVs(dimension),
                                     m_sumOfCrossProdRVs(dimension, Array(dimension)) {}

void math::Stat::add(Array randomVariables)
{
    if (randomVariables.size() != m_dim)
        throw std::out_of_range("Stat::add : argument size does not match object dimension.");

    for (unsigned int i = 0; i < m_dim; ++i)
    {
        m_sumOfRVs[i] += randomVariables[i];
        for (unsigned int j = i; j < m_dim; ++j)
            m_sumOfCrossProdRVs[i][j] = m_sumOfCrossProdRVs[j][i]  += randomVariables[i]*randomVariables[j];
    }
    ++m_counter;

    return;
}

Array math::Stat::mean() const
{
    checkCounter();
    Array meanValues;
    for (const auto &values : m_sumOfRVs)
        meanValues.push_back(values / m_counter);

    return meanValues;
}

Array math::Stat::variance() const
{
    checkCounter();
    Array varianceValues;
    for (unsigned int i = 0; i < m_dim; ++i)
    {
        const double var = (m_sumOfCrossProdRVs[i][i] - m_sumOfRVs[i] * m_sumOfRVs[i] / m_counter) / m_counter;
        varianceValues.push_back(var);
    }

    return varianceValues;
}

Array math::Stat::stdDev() const
{
    checkCounter();
    Array stdDevValues;
    for (unsigned int i = 0; i < m_dim; ++i)
    {
        const double stdDev = sqrt(
                (m_sumOfCrossProdRVs[i][i] - m_sumOfRVs[i] * m_sumOfRVs[i] / m_counter) / m_counter);
        stdDevValues.push_back(stdDev);
    }
    return stdDevValues;
}

Array math::Stat::stdError() const
{
    checkCounter();
    Array stdError;
    for (unsigned int i = 0; i < m_dim; ++i)
    {
        const double stdErr =
                sqrt((m_sumOfCrossProdRVs[i][i] - m_sumOfRVs[i] * m_sumOfRVs[i] / m_counter) / m_counter) /
                sqrt(m_counter);
        stdError.push_back(stdErr);
    }
    return stdError;
}

Matrix math::Stat::covariance() const
{
    checkCounter();
    Matrix covarianceValues(m_dim, Array(m_dim));
    for (unsigned int row = 0; row < m_dim; ++row)
        for (unsigned int column = 0; column <= row; ++column) {
            const double covar =
                    (m_sumOfCrossProdRVs[row][column] - m_sumOfRVs[row] * m_sumOfRVs[column] / m_counter) / m_counter;
            covarianceValues[row][column] = covarianceValues[column][row] = covar;

    }
    return covarianceValues;
}

Matrix math::Stat::correlation() const
{
    checkCounter();
    Matrix correlationValues(m_dim, Array(m_dim));
    for (unsigned int row = 0; row < m_dim; ++row)
        for (unsigned int column = 0; column <= row; ++column)
        {
            const double covar =
                    (m_sumOfCrossProdRVs[row][column] - m_sumOfRVs[row]*m_sumOfRVs[column]/m_counter)/m_counter;
            const double rowStdDev =
                    sqrt((m_sumOfCrossProdRVs[row][row]- m_sumOfRVs[row]*m_sumOfRVs[row]/m_counter)/m_counter);
            const double columnStdDev =
                    sqrt((m_sumOfCrossProdRVs[column][column]- m_sumOfRVs[column]*m_sumOfRVs[column]/m_counter)/m_counter);
            correlationValues[row][column] = correlationValues[column][row]  = covar/(rowStdDev*columnStdDev);
        }

    return correlationValues;
}