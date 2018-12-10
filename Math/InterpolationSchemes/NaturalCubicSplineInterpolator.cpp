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
        auto previous = --it, next = ++it;
        const double value = 3*(next -> second - it -> second)/(next -> first - it -> first) -
                3*(it -> second - previous -> second)/(it -> first - previous -> first);
        alpha.push_back(value);

        //alpha(j) = 3*(yvals(j + 1) - yvals(j))/(xvals(j + 1) - xvals(j)) -...
        //3*(yvals(j) - yvals(j - 1))/(xvals(j) - xvals(j - 1));
    }

    std::vector<double> mu, z;
    mu.push_back(0), z.push_back(0);
    long i = 1;

    for (auto it = ++dataSet.begin(); it != --dataSet.end(); ++it)
    {
        auto previous = --it, next = ++it;
        const double l = 2*(next -> first - previous -> first) - (it -> first - previous -> first)*mu[i-1];
        mu.push_back((next -> first - it -> first)/l);
        z.push_back((alpha[i] - (it -> first - previous -> first)*z[i-1])/l);
        ++i;

        //l = 2*(xvals(j + 1) - xvals(j - 1)) - (xvals(j) - xvals(j - 1))*mu(j - 1);
        //mu(j) = (xvals(j + 1) - xvals(j))/l;
        //z(j) = (alpha(j) - (xvals(j) - xvals(j - 1))*z(j - 1))/l;
    }

    CSCoeffs coeffs;
    double x = dataSet.rbegin() -> first;
    coeffs.a = dataSet.rbegin() -> second, coeffs.b = 0, coeffs.c = 0, coeffs.d = 0;
    m_splineFunction.insert(std::make_pair(x, coeffs));
    i = N-1;

    for (auto it = --dataSet.rbegin(); it != dataSet.rend(); --it)
    {
        auto next = ++it;
        const double h = next -> first - it -> first;
        x = it -> first;
        coeffs.a = it -> second;
        coeffs.c = z[i] - mu[i]*m_splineFunction.at(next -> first).c;
        coeffs.b = (m_splineFunction.at(next -> first).a - coeffs.a)/h - h*(m_splineFunction.at(next -> first).c + 2*coeffs.c)/3;
        coeffs.d = (m_splineFunction.at(next -> first).c - coeffs.c)/(3*h);
        m_splineFunction.insert(std::make_pair(x, coeffs));
        --i;
        //m_splineFunction
        /*h = xvals(j + 1) - xvals(j);
        cs(j).x = xvals(j);
        cs(j).a = yvals(j);
        cs(j).c = z(j) - mu(j)*cs(j + 1).c;
        cs(j).b = (cs(j + 1).a - cs(j).a)/h - h*(cs(j + 1).c + 2*cs(j).c)/3;
        cs(j).d = (cs(j + 1).c - cs(j).c)/(3*h);*/
    }


}

void math::NaturalCubicSplineInterpolator::interpolate(std::map<double, double> &dataSet, double x) const
{
    //implement
}

void math::NaturalCubicSplineInterpolator::interpolatePoints(std::map<double, double> &dataSet,
                                                             const std::vector<double> &queryPoints) const
{
    //implement
}

std::unique_ptr<math::Interpolator> math::NaturalCubicSplineInterpolator::clone() const
{
    return std::unique_ptr<math::NaturalCubicSplineInterpolator>(new math::NaturalCubicSplineInterpolator(*this));
}
