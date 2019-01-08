//
// Created by Alberto Campi on 15/11/2018.
//

#ifndef QUANTLIB_CURVEBOOTSTRAPPER_H
#define QUANTLIB_CURVEBOOTSTRAPPER_H

#include "../../pricing.h"
#include <map>
#include <set>
#include "../DiscountFactors/DiscountFactor.h"
#include "../../../Math/math.h"
#include "../../../Common/DateUtils/DayCountConventionHelper.h"

using CurveMap = std::map<double, double>;

struct pricing::Curves
{
    CurveMap yieldCurve;
    CurveMap discountCurve;
    CurveMap forwardCurve;
};

class pricing::CurveBootstrapper
{
public:
    CurveBootstrapper(const math::Interpolator& interpolationScheme);
    CurveBootstrapper(const math::Interpolator& interpolationScheme, double tolerance);
    CurveBootstrapper(const pricing::CurveBootstrapper& rhsBootstrapper);

    pricing::Curves getBootstrappedCurves(const CurveMap& inputCurve, const std::set<double>& tenors) const;

private:
    std::unique_ptr<math::Interpolator> m_interpolator;
    double m_tolerance;
    //common::DayCountConventionHelper m_dcc;

    std::map<double, double> _getAccrualPeriods(const std::set<double>& tenors) const;

};


#endif //QUANTLIB_CURVEBOOTSTRAPPER_H
