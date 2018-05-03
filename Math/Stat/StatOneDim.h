//
// Created by Alberto Campi on 15/04/2018.
//

#ifndef QUANTLIB_STATONEDIM_H
#define QUANTLIB_STATONEDIM_H

#include "Stat.h"
#include "../math.h"

class math::StatOneDim : public math::Stat
{
public:
    StatOneDim();

    void add(double x);
    double mean() const;
    double variance() const;
    double stdDev() const;
    double stdError() const;

private:
    double m_sumOfRV;
    double m_sumOfSquaredRV;

};


#endif //QUANTLIB_STATONEDIM_H
