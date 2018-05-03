//
// Created by Alberto Campi on 14/04/2018.
//

#ifndef QUANTLIB_STAT_H
#define QUANTLIB_STAT_H

#include <vector>
#include "../math.h"

typedef std::vector<double> Array;
typedef std::vector<std::vector<double >> Matrix;


class math::Stat
{
public:
    Stat(unsigned int dimension);

    void add(Array randomVariables);
    Array mean() const;
    Array variance() const;
    Array stdDev() const;
    Array stdError() const;

    Matrix covariance() const;
    Matrix correlation() const;

protected:
    const unsigned int m_dim;
    unsigned long m_counter;

    void checkCounter() const;

private:
    Array m_sumOfRVs;
    Matrix m_sumOfCrossProdRVs;
};


#endif //QUANTLIB_STAT_H
