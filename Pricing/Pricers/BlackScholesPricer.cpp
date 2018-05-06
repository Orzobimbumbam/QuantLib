//
// Created by Alberto Campi on 01/05/2018.
//

#include "BlackScholesPricer.h"
#include "../../Math/math.h"


using namespace pricing;
using namespace common;
using namespace math;

BlackScholesPricer::BlackScholesPricer(double spot, double vol, double interestRate, const common::OptionDate &dates,
    double strike, PutCallFlag pcf, double dividendYield) :
        m_spot(spot*exp(interestRate*dates.getOptionYearsToSettlement())), m_vol(vol), m_r(interestRate), m_divYield(dividendYield),
        m_od(dates), m_putCallFlag(pcf), m_strike(strike) {}

double BlackScholesPricer::optionPrice() const
{
    const double df = exp(-m_r*m_od.getOptionYearsToMaturity());
    const double div = exp(-m_divYield*m_od.getOptionYearsToMaturity());

    return m_putCallFlag*m_spot*div*stdNormCdf(m_putCallFlag*dPlusMinus(1)) -
           m_putCallFlag*m_strike*df*stdNormCdf(m_putCallFlag*dPlusMinus(-1));
}

double BlackScholesPricer::dPlusMinus(short plusMinusFlag) const
{
    const double T = m_od.getOptionYearsToMaturity();
    return (log(m_spot/m_strike) + (m_r - m_divYield + plusMinusFlag*m_vol*m_vol/2)*T)/(m_vol*sqrt(T));
}

