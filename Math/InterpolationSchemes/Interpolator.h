//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_INTERPOLATOR_H
#define QUANTLIB_INTERPOLATOR_H

#include "../math.h"
#include <map>
#include <set>


class math::Interpolator
{
public:
    virtual std::pair<double, double> interpolate(const std::map<double, double>& dataSet, double x) = 0;
    virtual std::map<double, double> interpolatePoints(const std::map<double, double>& dataSet,
                                                       const std::set<double>& queryPoints) = 0;
    virtual std::unique_ptr<math::Interpolator> clone() const = 0;
    //virtual math::Interpolator* clone() const = 0;

    virtual ~Interpolator() = default;

};


struct math::CSCoeffs
{
    CSCoeffs() = default;
    CSCoeffs(double aConst, double bLin, double cQuad, double dCub);
    double a;   //constant coefficient -> y-value at node
    double b;   //linear coefficient -> related to first derivative
    double c;   //quadratic coefficient -> related to second derivative
    double d;   //cubic coefficient

    CSCoeffs& operator=(const CSCoeffs& rhsCSCoeffs) = default;
    bool operator==(const CSCoeffs& rhsCSCoeffs);
    bool operator!=(const CSCoeffs& rhsCSCoeffs);
};


using CSpline = std::map<double, math::CSCoeffs>;

#endif //QUANTLIB_INTERPOLATOR_H
