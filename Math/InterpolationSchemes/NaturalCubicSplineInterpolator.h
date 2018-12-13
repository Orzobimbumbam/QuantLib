//
// Created by Alberto Campi on 10/12/2018.
//

#ifndef QUANTLIB_NATURALCUBICSPLINEINTERPOLATOR_H
#define QUANTLIB_NATURALCUBICSPLINEINTERPOLATOR_H

#include "Interpolator.h"


class math::NaturalCubicSplineInterpolator : public math::Interpolator
{
public:
    NaturalCubicSplineInterpolator() = default;

    void interpolate(std::map<double, double>& dataSet, double x) override;
    void interpolatePoints(std::map<double, double>& dataSet, const std::vector<double>& queryPoints) override;
    std::unique_ptr<math::Interpolator> clone() const override;

    void fitSpline(const std::map<double, double>& dataSet);
    CSpline getCoeffs() const;


private:
    CSpline m_splineFunction;

};


#endif //QUANTLIB_NATURALCUBICSPLINEINTERPOLATOR_H
