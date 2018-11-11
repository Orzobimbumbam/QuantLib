//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_INTERPOLATOR_H
#define QUANTLIB_INTERPOLATOR_H

#include "../math.h"
#include <map>

class math::Interpolator
{
public:
    virtual void interpolate(std::map<double, double>& dataSet, double x) const = 0;
    virtual ~Interpolator() = default;
};


#endif //QUANTLIB_INTERPOLATOR_H
