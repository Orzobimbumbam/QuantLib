//
// Created by Alberto Campi on 15/05/2018.
//

#include "GeometricBM.h"

pricing::GeometricBM::GeometricBM(const math::RandomNumberGenerator &rng, double interestRate, double volatility, bool isExoticPayOff) :
        StochasticModel(rng), m_ir(interestRate), m_vol(volatility), m_exoticFlag(isExoticPayOff) {}

PathMap pricing::GeometricBM::SDE(double spot, const common::OptionDate &od) const
{
    const unsigned long days = od.getDaysToMaturity();
    const double T = od.getOptionYearsToMaturity();
    const double deltaT = T/days;

    PathMap gbmPath;

    if (m_exoticFlag)
        getExactSpotPath(gbmPath, spot, od, deltaT);
    else
        getTerminalSpotValue(gbmPath, spot, od);

    return gbmPath;
}

void pricing::GeometricBM::getExactSpotPath(PathMap &pm, double spot, const common::OptionDate &od, double deltaT) const
{
    const unsigned long days = od.getDaysToMaturity();
    RandomArray bmPath = m_rngPtr -> generateArray(days);
    double movingSpotValue = spot;
    boost::gregorian::date t = od.getSettlementDate();

    for (unsigned long i = 0; i < days; ++i)
    {
        movingSpotValue *= exp((m_ir - m_vol*m_vol/2)*deltaT + m_vol*sqrt(deltaT)*bmPath[i]);
        t += boost::gregorian::days(1);
        pm.insert(std::make_pair(t, movingSpotValue));
    }
    return;
}

void pricing::GeometricBM::getTerminalSpotValue(PathMap &pm, double spot, const common::OptionDate &od) const
{
    const double terminalBmValue = m_rngPtr -> generate();
    const double T = od.getOptionYearsToMaturity();
    const double terminalSpotValue = spot*exp((m_ir - m_vol*m_vol/2)*T + m_vol*sqrt(T)*terminalBmValue);
    pm.insert(std::make_pair(od.getMaturityDate(), terminalSpotValue));

    return;
}