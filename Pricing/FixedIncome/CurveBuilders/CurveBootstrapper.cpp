//
// Created by Alberto Campi on 15/11/2018.
//

#include "CurveBootstrapper.h"

pricing::CurveBootstrapper::CurveBootstrapper(double annualRate, double accrualPeriodInYears) :
        m_rate(annualRate), m_tau(accrualPeriodInYears), m_dfSum(1) {}

/*CurveMap pricing::CurveBootstrapper::getBootstrappedDiscountCurve(const CurveMap &curve, const std::set<double>& tenors)
{
    CurveMap btDCurve;
    const double firstCurveTenor = curve.begin() -> first;
    const double lastCurveTenor = curve.rbegin() -> first;

    for (auto& curveIt : curve)
    {
        for (auto tenorsIt = tenors.begin(); tenorsIt != tenors.end(); ++tenorsIt)
        {
            if (*tenorsIt < firstCurveTenor)
            {
                //interpolate between zero and firstCurveTenor
            }
            if (*tenorsIt > firstCurveTenor)
            {
                auto prevTenorsIt = --tenorsIt;
                btDCurve.at(*tenorsIt) = btDCurve.at(*prevTenorsIt);
            }
            if (*tenorsIt == curveIt.first)
                btDCurve.at(*tenorsIt) = (1 - m_rate*m_tau*m_dfSum)/(1 + m_rate*m_tau);
            else
            {
                if ()
            }
        }

    }
    return std::map<double, double>();
}*/
