//
// Created by Alberto Campi on 11/11/2018.
//

#include "LinearInterpolator.h"

void math::LinearInterpolator::interpolate(std::map<double, double> &dataSet, double x) const
{
    auto i = dataSet.begin();
    //check whether the map contains at least two data points
    if (dataSet.size() < 2)
    {
        throw std::runtime_error("E: math::LinearInterpolator::interpolate : insufficient data for interpolation.");
    }

    //handle lower extrapolation
    if (x <= i -> first)
    {
        dataSet[x] = i -> second;
        return;
    }

    //handle interpolation
    for (i = dataSet.begin(); i != dataSet.end(); ++i)
    {
        if(i -> first > x)
        {
            auto previous = i;
            --previous;
            const double x0 = previous -> first;
            const double y0 = previous -> second;
            const double x1 = i -> first;
            const double y1 = i -> second;
            dataSet[x] = y0 + (x - x0)*((y1 - y0)/(x1 - x0));
            return;
        }
    }
    //handle upper extrapolation
    if (i == dataSet.end())
    {
        --i;
        dataSet[x] = i -> second;
        return;
    }
}

void math::LinearInterpolator::interpolatePoints(std::map<double, double>& dataSet, const std::vector<double>& queryPoints) const
{
    for (const auto &it : queryPoints)
        interpolate(dataSet, it);

}

std::unique_ptr<math::Interpolator> math::LinearInterpolator::clone() const
{
    return std::unique_ptr<math::LinearInterpolator>(new math::LinearInterpolator(*this));
}
