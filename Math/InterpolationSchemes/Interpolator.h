//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_INTERPOLATOR_H
#define QUANTLIB_INTERPOLATOR_H

#include "../math.h"
#include <map>
#include <vector>


class math::Interpolator
{
public:
    virtual void interpolate(std::map<double, double>& dataSet, double x) const = 0;
    virtual void interpolatePoints(std::map<double, double>& dataSet, const std::vector<double>& queryPoints) const = 0;
    virtual std::unique_ptr<math::Interpolator> clone() const = 0;

    virtual ~Interpolator() = default;

};


struct math::CSCoeffs
{
    double a;   //constant coefficient -> y-value at node
    double b;   //linear coefficient -> related to first derivative
    double c;   //quadratic coefficient -> related to second derivative
    double d;   //cubic coefficient
};

using CSpline = std::map<double, math::CSCoeffs>;

#endif //QUANTLIB_INTERPOLATOR_H
