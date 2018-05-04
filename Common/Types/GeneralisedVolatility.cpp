//
// Created by Alberto Campi on 03/05/2018.
//

#include "GeneralisedVolatility.h"
#include "../../Math/math.h"

common::GeneralisedVolatility::GeneralisedVolatility(const VolMap &data)
        : GeneralisedMarketDataType(data) {}

double common::GeneralisedVolatility::getRMSSquaredVolatility() const
{
    const double stepSize = getIntegrationStepSize();
    math::NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    const double T = m_data.rbegin() -> first - stepSize;

    return sqrt(1./T*integrator.integrateBySimpson(*this, stepSize, m_data.rbegin() -> first));
}