//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_LINEARINTERPOLATOR_H
#define QUANTLIB_LINEARINTERPOLATOR_H

#include "Interpolator.h"

class math::LinearInterpolator : public math::Interpolator
{
public:
    void interpolate(std::map<double, double>& dataSet, double x) const override;

};


#endif //QUANTLIB_LINEARINTERPOLATOR_H
