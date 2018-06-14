//
// Created by Alberto Campi on 03/06/2018.
//

#include "MonteCarloPricer.h"
#include "../../Math/Stat/StatOneDim.h"

pricing::MonteCarloPricer::MonteCarloPricer(const pricing::StochasticModel &model, const pricing::Option &option,
                                            const common::Numeraire &numeraire, double spot, unsigned long nPaths) :
        m_mdl(model.clone()), m_option(option.clone()), m_numeraire(numeraire.clone()), m_spot(spot), m_nPaths(nPaths), m_stdError(0) {}

double pricing::MonteCarloPricer::stdError() const
{
    return m_stdError;
}

void pricing::MonteCarloPricer::setPathNumber(unsigned long nPaths)
{
    m_nPaths = nPaths;
}

void pricing::MonteCarloPricer::setSpot(double spot)
{
    m_spot = spot;
}

void pricing::MonteCarloPricer::setOption(const pricing::Option &option)
{
    m_option = option.clone();
}

void pricing::MonteCarloPricer::setModel(const pricing::StochasticModel &model)
{
    m_mdl = model.clone();
}

void pricing::MonteCarloPricer::setNumeraire(const common::Numeraire &numeraire)
{
    m_numeraire = numeraire.clone();
}

double pricing::MonteCarloPricer::optionPrice() const
{
    math::StatOneDim stat;
    const double expiry = m_option -> getOptionYearsToMaturity();

    for (unsigned long i = 0; i < m_nPaths; ++i)
    {
        const PathMap randomSpotPath = m_mdl -> SDE(m_spot, m_option -> getOptionDate());
        const double payOff = m_option -> getOptionPayOff(randomSpotPath);
        stat.add(m_numeraire -> operator()(expiry)*payOff);
    }

    m_stdError = stat.stdDev()/sqrt(m_nPaths);
    return stat.mean();
}
