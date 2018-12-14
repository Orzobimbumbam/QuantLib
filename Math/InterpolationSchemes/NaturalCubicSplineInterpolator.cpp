//
// Created by Alberto Campi on 10/12/2018.
//

#include "NaturalCubicSplineInterpolator.h"

void math::NaturalCubicSplineInterpolator::fitSpline(const std::map<double, double> &dataSet)
{
    if (dataSet.size() < 2)
    {
        throw std::runtime_error("E: math::NaturalCubicSplineInterpolator::fitSpline : insufficient data for interpolation.");
    }

    const long N = dataSet.size();
    std::vector<double> alpha;

    for (auto it = ++dataSet.begin(); it != --dataSet.end(); ++it)
    {
        auto previous = it, next = it;
        --previous, ++next;
        const double value = 3*(next -> second - it -> second)/(next -> first - it -> first) -
                3*(it -> second - previous -> second)/(it -> first - previous -> first);
        alpha.push_back(value);
    }

    std::vector<double> mu, z;
    mu.push_back(0), z.push_back(0);
    long i = 1;

    for (auto it = ++dataSet.begin(); it != --dataSet.end(); ++it)
    {
        auto previous = it, next = it;
        --previous, ++next;
        const double l = 2*(next -> first - previous -> first) - (it -> first - previous -> first)*mu[i-1];
        mu.push_back((next -> first - it -> first)/l);
        z.push_back((alpha[i-1] - (it -> first - previous -> first)*z[i-1])/l);
        ++i;
    }

    CSCoeffs coeffs{};
    double x = dataSet.rbegin() -> first;
    coeffs.a = dataSet.rbegin() -> second, coeffs.b = 0, coeffs.c = 0, coeffs.d = 0;
    m_splineFunction.insert(std::make_pair(x, coeffs));
    i = N-2;

    for (auto it = ++dataSet.rbegin(); it != dataSet.rend(); ++it)
    {
        auto next = it.base();
        //--next;
        const double h = next -> first - it -> first;
        x = it -> first;
        coeffs.a = it -> second;
        coeffs.c = z[i] - mu[i]*m_splineFunction.at(next -> first).c;
        coeffs.b = (m_splineFunction.at(next -> first).a - coeffs.a)/h - h*(m_splineFunction.at(next -> first).c + 2*coeffs.c)/3;
        coeffs.d = (m_splineFunction.at(next -> first).c - coeffs.c)/(3*h);
        m_splineFunction.insert(std::make_pair(x, coeffs));
        --i;
    }
}

CSpline math::NaturalCubicSplineInterpolator::getCoeffs() const
{
    return m_splineFunction;
}

void math::NaturalCubicSplineInterpolator::interpolate(std::map<double, double> &dataSet, double x)
{
    fitSpline(dataSet);

    auto it = m_splineFunction.begin();
    if (x < it -> first)
    {
        const double deltax = x - it -> first;
        const CSCoeffs thisCoeff = it -> second;

        auto next = it;
        ++next;
        const CSCoeffs nextCoeff = next -> second;

        const double y = thisCoeff.a + nextCoeff.b*deltax + thisCoeff.c*deltax*deltax + thisCoeff.d*deltax*deltax*deltax;
        dataSet.insert(std::make_pair(x, y));
    }
    else
    {
        for (; it != --m_splineFunction.end(); ++it)
        {
            if (it -> first > x)
            {
                auto previous = it;
                --previous;
                const double deltax = x - previous -> first;
                const CSCoeffs prevCoeff = previous -> second;

                const double y = prevCoeff.a + prevCoeff.b*deltax + prevCoeff.c*deltax*deltax + prevCoeff.d*deltax*deltax*deltax;
                dataSet.insert(std::make_pair(x, y));
                break;
            }
        }

        if (it == --m_splineFunction.end())
        {
            const double deltax = x - it -> first;
            const CSCoeffs thisCoeff = it -> second;

            auto previous = it;
            --previous;
            const CSCoeffs prevCoeff = previous -> second;
            const double h = it -> first - previous -> first;
            const double b = prevCoeff.b + 2*prevCoeff.c*h + 3*prevCoeff.d*h*h;
            const double y = thisCoeff.a + b*deltax + prevCoeff.c*deltax*deltax + prevCoeff.d*deltax*deltax*deltax;
            dataSet.insert(std::make_pair(x, y));
        }
    }
    return;
}

void math::NaturalCubicSplineInterpolator::interpolatePoints(std::map<double, double> &dataSet,
                                                             const std::vector<double> &queryPoints)
{
    for (const auto& it : queryPoints)
        interpolate(dataSet, it);
}

std::unique_ptr<math::Interpolator> math::NaturalCubicSplineInterpolator::clone() const
{
    return std::unique_ptr<math::NaturalCubicSplineInterpolator>(std::make_unique<math::NaturalCubicSplineInterpolator>(*this));
}
