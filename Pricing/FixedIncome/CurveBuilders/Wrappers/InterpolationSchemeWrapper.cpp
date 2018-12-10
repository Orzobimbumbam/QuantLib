//
// Created by Alberto Campi on 14/11/2018.
//

#include "InterpolationSchemeWrapper.h"

pricing::InterpolationSchemeWrapper::InterpolationSchemeWrapper(const math::Interpolator& interpolator,
                                                                const std::pair<double, double> &prevCurvePoint, double nextPointTenor,
                                                                double tenor) :

    m_tenor(tenor), m_nextPointTenor(nextPointTenor), m_prevCurvePoint(prevCurvePoint),
    m_interpPtr(interpolator.clone()) {}

std::pair<double, double> pricing::InterpolationSchemeWrapper::interpolatedCurvePoint(double nextCurveValue) const
{
    const std::pair<double, double> nextCurvePoint = std::make_pair(m_nextPointTenor, nextCurveValue);
    std::map<double, double> interpolationSegment = {m_prevCurvePoint, nextCurvePoint};
    m_interpPtr -> interpolate(interpolationSegment, m_tenor);

    return std::make_pair(m_tenor, interpolationSegment.at(m_tenor));
}


