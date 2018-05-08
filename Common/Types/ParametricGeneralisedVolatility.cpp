//
// Created by Alberto Campi on 03/05/2018.
//

#include "ParametricGeneralisedVolatility.h"

using namespace common;

ParametricGeneralisedVolatility::ParametricGeneralisedVolatility(const common::OptionDate &dates, double a, double b,
                                                                 double c, double d) :

        GeneralisedVolatility(), m_size(getSize(dates)), m_a(a), m_b(b), m_c(c), m_d(d),
        m_yearsToMaturity(dates.getOptionYearsToMaturity())
{
    getData();
}

void ParametricGeneralisedVolatility::setOLSParams(double a, double b, double c, double d)
{
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;

    return;
}

long ParametricGeneralisedVolatility::size() const
{
    return m_size;
}

VolMap ParametricGeneralisedVolatility::get() const
{
    return m_data;
}

long ParametricGeneralisedVolatility::getSize(const common::OptionDate &dates) const
{
    return (dates.getMaturityDate() - dates.getSettlementDate()).days();
}

double ParametricGeneralisedVolatility::getParametricSquaredVolatility(double t) const
{
    return pow((m_a + m_b*(m_yearsToMaturity - t))*exp(-m_c*(m_yearsToMaturity - t)) + m_d, 2);
}

double ParametricGeneralisedVolatility::operator()(double t) const
{
    return getParametricSquaredVolatility(t);
}

void ParametricGeneralisedVolatility::getData()
{
    const double h = m_yearsToMaturity/m_size;
    double t = 0;
    //m_data.insert(std::make_pair(t, getParametricVolatilitySquared(t)));
    for (unsigned long i = 0; i < m_size; ++i)
    {
        t += h;
        m_data.insert(std::make_pair(t, getParametricSquaredVolatility(t)));
    }
}

double ParametricGeneralisedVolatility::getIntegrationStepSize() const
{
    return m_yearsToMaturity/m_size;
}