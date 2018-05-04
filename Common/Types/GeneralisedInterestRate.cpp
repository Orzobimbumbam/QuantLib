//
// Created by Alberto Campi on 03/05/2018.
//

#include "GeneralisedInterestRate.h"
#include "../../Math/math.h"

using namespace common;

GeneralisedInterestRate::GeneralisedInterestRate(const IRMap &data) : GeneralisedMarketDataType(data) {}

double GeneralisedInterestRate::getAverageRate() const
{
    const double stepSize = getIntegrationStepSize();
    math::NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    const double T = m_data.rbegin() -> first - stepSize;

    return 1./T*integrator.integrateBySimpson(*this, stepSize, m_data.rbegin() -> first);
}