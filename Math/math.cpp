//
// Created by Alberto Campi on 01/05/2018.
//

#include "math.h"

//GLOBAL NAMESPACE FUNCTION DEFINITIONS
double math::stdNormCdf(double x)
{
return (1 + std::erf(x/sqrt(2)))/2;
}

double math::stdNormPdf(double x)
{
    using namespace boost::math::constants;
    return 1./root_two_pi<double>()*exp(-x*x/2.);
}

//LegendrePolynomials class definition
math::LegendrePolynomials::LegendrePolynomials() : m_P(1), m_dP(0), m_N(0), m_areComputed(false)
{}

math::LegendrePolynomials::LegendrePolynomials(unsigned long degree) : m_P(1), m_dP(0), m_N(degree), m_areComputed(false)
{}

void math::LegendrePolynomials::setDegree(unsigned long degree)
{
    m_N = degree;
    m_areComputed = false;
}

double math::LegendrePolynomials::P(double x) const
{
    _compute(x);
    return m_P;
}

double math::LegendrePolynomials::dP(double x) const
{
    _compute(x);
    return m_dP;
}

void math::LegendrePolynomials::_compute(double x) const
{
    if ((m_areComputed && m_x == x) || m_N == 0)
        return;

    double P1 = x, P2 = 1;
    if (m_N == 1)
    {
        m_P = P1;
        m_dP = 1;
        return;
    }
    else
    {
        for (unsigned long i = 2; i <= m_N; ++i)
        {
            m_P = ((2*i - 1)*x*P1 - (i - 1)*P2)/i;
            m_dP = (x*m_P - P1)*i/(x*x - 1);
            P2 = P1, P1 = m_P;
        }
    }

    m_x = x, m_areComputed = true;

}
