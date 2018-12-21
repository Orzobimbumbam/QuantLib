//
// Created by Alberto Campi on 03/05/2018.
//

#include "GeneralisedVolatility.h"
#include "../../Math/math.h"

common::GeneralisedVolatility::GeneralisedVolatility(const VolMap &data)
        : GeneralisedMarketDataType(data) {}

common::GeneralisedVolatility::GeneralisedVolatility(const std::map<boost::gregorian::date, double> &data,
                                                     DayCountConventionInUse dcc) : GeneralisedMarketDataType(data, dcc) {}

double common::GeneralisedVolatility::getRMSSquaredVolatility() const
{
    //const double stepSize = _getIntegrationStepSize();
    math::NumQuadrature<GeneralisedMarketDataType, &GeneralisedMarketDataType::operator()> integrator{};
    std::set<double> mesh;
    for (const auto& it : m_data)
        mesh.insert(it.first);

    const double T = m_data.rbegin() -> first - m_data.begin() -> first;

    return sqrt(1./T*integrator.integrateByTrapezoid(*this, mesh));
}