//
// Created by Alberto Campi on 03/05/2018.
//

#include "GeneralisedInterestRate.h"
#include "../../Math/math.h"

using namespace common;

GeneralisedInterestRate::GeneralisedInterestRate(const IRMap &data) : GeneralisedMarketDataType(data) {}

GeneralisedInterestRate::GeneralisedInterestRate(const std::map<boost::gregorian::date, double> &data, DayCountConventionInUse dcc) :
        GeneralisedMarketDataType(data, dcc){}

double GeneralisedInterestRate::getAverageRate() const
{
    /*
    const double stepSize = _getIntegrationStepSize();
    math::NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator(stepSize);
    const double T = m_data.rbegin() -> first - stepSize;

    return 1./T*integrator.integrateBySimpson(*this, stepSize, m_data.rbegin() -> first);*/
    math::NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator;
    std::set<double> mesh;
    for (const auto& it : m_data)
        mesh.insert(it.first);

    const double T = m_data.rbegin() -> first - m_data.begin() -> first;
    return 1./T*integrator.integrateByTrapezoid(*this, mesh);
}