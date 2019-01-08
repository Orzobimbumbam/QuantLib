//
// Created by Alberto Campi on 15/11/2018.
//

#include "CurveBootstrapper.h"
#include "../../../Math/InterpolationSchemes/interpolator.h"

pricing::CurveBootstrapper::CurveBootstrapper(const math::Interpolator& interpolationScheme) :
        m_interpolator(interpolationScheme.clone()), m_tolerance(1e-10) {}

pricing::CurveBootstrapper::CurveBootstrapper(const math::Interpolator &interpolationScheme, double tolerance) :
        m_interpolator(interpolationScheme.clone()), m_tolerance(tolerance) {}

pricing::CurveBootstrapper::CurveBootstrapper(const pricing::CurveBootstrapper &rhsBootstrapper) :
        m_interpolator(rhsBootstrapper.m_interpolator -> clone()), m_tolerance(rhsBootstrapper.m_tolerance) {}

pricing::Curves pricing::CurveBootstrapper::getBootstrappedCurves(const CurveMap& inputCurve, const std::set<double>& tenors) const
{
    CurveMap guessRates, yieldCurve, discountCurve;
    std::map<double, double> accrualPeriods = _getAccrualPeriods(tenors);

    for (const auto& it : inputCurve)
    {
        const double r = 1./it.first*log(1 + it.first*it.second);
        guessRates.emplace(it.first, r);
    }

    unsigned long iterCounter = 0;

    while (true)
    {
        CurveMap interpolatedCurve;
        ++iterCounter;
        for (const auto& it : tenors)
        {
            const std::pair<double, double > interpolatedCurvePoint = m_interpolator -> interpolate(guessRates, it);
            interpolatedCurve.emplace(interpolatedCurvePoint);

            const double df = exp(-it*interpolatedCurvePoint.second);
            discountCurve[it] = df;
        }

        double maxDistance = 0;
        for (const auto& it : inputCurve)
        {
            double dfSum = 0;
            auto runningPtr = tenors.begin();
            while (runningPtr != tenors.end() && *runningPtr < it.first)
            {
                dfSum += accrualPeriods.at(*runningPtr)*discountCurve.at(*runningPtr);
                ++runningPtr;
            }

            yieldCurve[it.first] = -1./it.first*log((1 - it.second*dfSum)/(1 + accrualPeriods.at(it.first)*it.second));
            if (std::abs(yieldCurve.at(it.first) - guessRates.at(it.first)) > maxDistance)
                maxDistance = std::abs(yieldCurve.at(it.first) - guessRates.at(it.first));
        }

        if (maxDistance < m_tolerance)
            break;
        else
        {
            //guessRates.clear();
            guessRates = yieldCurve;
        }
    }

    Curves bootstrappedCurves;bootstrappedCurves.yieldCurve = yieldCurve;
    bootstrappedCurves.discountCurve = discountCurve;
    //TODO: add logic for forward rate

    return bootstrappedCurves;
}

std::map<double, double> pricing::CurveBootstrapper::_getAccrualPeriods(const std::set<double> &tenors) const
{
    std::map<double, double> alphaI = {{*tenors.begin(), *tenors.begin()}};
    for (auto it = ++tenors.begin(); it != tenors.end(); ++it)
    {
        auto prevIt = it;
        --prevIt;

        alphaI.emplace(*it, *it - *prevIt);
    }

    return alphaI;
}