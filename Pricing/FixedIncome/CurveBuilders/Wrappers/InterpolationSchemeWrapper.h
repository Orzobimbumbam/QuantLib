//
// Created by Alberto Campi on 14/11/2018.
//

#ifndef QUANTLIB_INTERPOLATIONSCHEMEWRAPPER_H
#define QUANTLIB_INTERPOLATIONSCHEMEWRAPPER_H

#include <utility>
#include <memory>
#include "../../../../Math/InterpolationSchemes/Interpolator.h"

class pricing::InterpolationSchemeWrapper
{
public:
    InterpolationSchemeWrapper(const math::Interpolator& interpolator, const std::pair<double, double>& prevCurvePoint,
                               double nextPointTenor, double tenor);
    std::pair<double, double> interpolatedCurvePoint(double nextCurveValue) const;

private:
    double m_tenor, m_nextPointTenor;
    std::pair<double, double> m_prevCurvePoint;
    const std::shared_ptr<math::Interpolator> m_interpPtr;
};


#endif //QUANTLIB_INTERPOLATIONSCHEMEWRAPPER_H
