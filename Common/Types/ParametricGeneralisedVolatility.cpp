//
// Created by Alberto Campi on 03/05/2018.
//

#include "ParametricGeneralisedVolatility.h"

using namespace common;

ParametricGeneralisedVolatility::ParametricGeneralisedVolatility(const common::OptionDate &dates, double a, double b,
                                                                 double c, double d) :

        GeneralisedVolatility(), m_size(_getSize(dates)), m_a(a), m_b(b), m_c(c), m_d(d),
        m_yearsToMaturity(dates.getOptionYearsToMaturity())
{
    //getData();
    _dateToDoubleMapper(_getDateMap(dates), dates.getDayCountConventionInUse());
}

void ParametricGeneralisedVolatility::setOLSParams(double a, double b, double c, double d)
{
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;
}

long ParametricGeneralisedVolatility::size() const
{
    return m_size;
}

VolMap ParametricGeneralisedVolatility::get() const
{
    return m_data;
}

long ParametricGeneralisedVolatility::_getSize(const common::OptionDate &dates) const
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

double ParametricGeneralisedVolatility::operator()(boost::gregorian::date t) const
{
    return getParametricSquaredVolatility(m_dateDoubleMap.at(t));
}
/*
double ParametricGeneralisedVolatility::_getIntegrationStepSize() const
{
    return m_yearsToMaturity/m_size;
}
*/
std::map<boost::gregorian::date, double> ParametricGeneralisedVolatility::_getDateMap(const common::OptionDate &dates) const
{
    const long days = dates.getDaysToMaturity();
    const double deltaT = dates.getOptionYearsToMaturity()/days;
    std::map<boost::gregorian::date, double> volMapDate;

    const boost::gregorian::date D = dates.getSettlementDate();
    double t = 0;
    //volMapDate.insert(std::make_pair(D, this -> operator()(t)));

    for (unsigned long i = 0; i <= days; ++i)
    {
        volMapDate.insert(std::make_pair(D + boost::gregorian::days(i), this -> operator()(t)));
        t += deltaT;
    }
    return volMapDate;
}