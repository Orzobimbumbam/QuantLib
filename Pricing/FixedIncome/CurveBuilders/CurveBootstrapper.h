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

using CurveMap = std::map<double, double>;

class pricing::CurveBootstrapper
{
public:
    CurveBootstrapper(double annualRate, double accrualPeriodInYears);

    CurveMap getBootstrappedDiscountCurve(const CurveMap& curve, const std::set<double>& tenors);

private:
    double m_rate, m_tau;
    double m_dfSum;

};


#endif //QUANTLIB_CURVEBOOTSTRAPPER_H
