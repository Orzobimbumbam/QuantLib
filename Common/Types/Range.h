//
// Created by Alberto Campi on 05/06/2018.
//

#ifndef QUANTLIB_RANGE_H
#define QUANTLIB_RANGE_H

#include <set>
#include "../Common.h"

typedef std::set<double> Partition;

class common::Range {
public:
    Range(double lower, double upper);
    Range(double lower, double upper, double meshSize);

    double getLower() const;
    double getUpper() const;
    double getMeshSize() const;

    void setLower(double lower);
    void setUpper(double upper);

    Partition getPartition() const;

private:
    double m_lower, m_upper;
    const double m_meshSize;
    Partition m_partition;

    void partition();
};


#endif //QUANTLIB_RANGE_H
