//
// Created by Alberto Campi on 06/05/2018.
//

#include "BlackPricer.h"
#include "../../Math/math.h"

pricing::BlackPricer::BlackPricer(double futureSpot, double rmsVol, const common::Numeraire &numeraire,
                                  const common::OptionDate &dates, double strike, PutCallFlag pcf) :

m_futureSpot(futureSpot), m_rmsVol(rmsVol), m_discountFactor(numeraire(dates.getOptionYearsToMaturity())),
m_od(dates), m_strike(strike), m_putCallFlag(pcf) {}

double pricing::BlackPricer::optionPrice() const
{
    return m_discountFactor*(m_putCallFlag*m_futureSpot*math::stdNormCdf(m_putCallFlag*dPlusMinus(1)) -
           m_putCallFlag*m_strike*math::stdNormCdf(m_putCallFlag*dPlusMinus(-1)));
}

double pricing::BlackPricer::dPlusMinus(short plusMinusFlag) const
{
    const double T = m_od.getOptionYearsToMaturity();
    return (log(m_futureSpot/m_strike) + plusMinusFlag*m_rmsVol*m_rmsVol/2*T)/(m_rmsVol*sqrt(T));
}

double pricing::BlackPricer::putCallParity(double price) const
{
    return price - m_putCallFlag*m_discountFactor*(m_futureSpot - m_strike);
}
