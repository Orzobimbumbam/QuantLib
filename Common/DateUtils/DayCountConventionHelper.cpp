//
// Created by Alberto Campi on 25/04/2018.
//

#include "DayCountConventionHelper.h"
#include <cmath>

using namespace common;

DayCountConventionHelper::DayCountConventionHelper(DayCountConventionInUse dcc) : m_isActual(false)
{
    dayCountConventionMapper(dcc);
}

void DayCountConventionHelper::dayCountConventionMapper(DayCountConventionInUse dcc)
{
    switch (dcc)
    {
        case Simple:
            m_isActual = true, m_daysInYear = 365;
            break;

        case Act_Act:
            m_isActual = true , m_daysInYear = 0;
            break;

        case Thirty_ThreeSixty:
            m_daysInYear = 360, m_daysInMonth = 30;
            break;

        case Thirty_ThreeSixtyFive:
            m_daysInYear = 365, m_daysInMonth = 30;
            break;

        case Thirty_TwoFiftyTwo:
            m_daysInYear = 252, m_daysInMonth = 30;

        default:
            throw std::runtime_error("DayCountConventionHelper::dayCountConventionMapper : unknown daycount convention.");

    }
    return;
}

double DayCountConventionHelper::getAccrualPeriodInYears(const boost::gregorian::date& D1,
                                                                                  const boost::gregorian::date& D2) const
{
    double y;
    if (!m_isActual)
    {
        y = getAccrualPeriodInYearsNoActual(D1, D2);
    }
    else
    {
        if (m_daysInYear == 0) //Act/Act
            y = getAccrualPeriodInYearsActual(D1, D2);
        else
            y = (D2 - D1).days()/365.;
    }

    return y;
}

unsigned long DayCountConventionHelper::getDurationLengthInDays(double durationLengthInYears) const
{
    return static_cast<unsigned long>(durationLengthInYears*m_daysInYear);
}

double DayCountConventionHelper::getAccrualPeriodInYearsNoActual(const boost::gregorian::date& D1,
                                                                                const boost::gregorian::date& D2) const
{
    const unsigned long dayD1 = D1.day(), dayD2 = D2.day(), monthD1 = D1.month(), monthD2 = D2.month(),
            yearD1 = D1.year(), yearD2 = D2.year();

    const double deltaDays = std::abs(static_cast<double>(dayD1 - dayD2));
    const double deltaMonths = std::abs(static_cast<double>(monthD1 - monthD2));
    const double deltaYears = std::abs(static_cast<double>(yearD1 - yearD2));

    return (deltaDays + deltaMonths*m_daysInMonth + deltaYears*m_daysInYear )/m_daysInYear;
}

double DayCountConventionHelper::getAccrualPeriodInYearsActual(const boost::gregorian::date& D1,
                                                        const boost::gregorian::date& D2) const
{
    double y = 0;

    const boost::gregorian::date_period dp(D1, D2);
    boost::gregorian::date rolledD1 = D1;
    for (boost::gregorian::year_iterator yit = dp.begin(); ; ++yit)
    {
        const boost::gregorian::date rolledDate((rolledD1 + boost::gregorian::years(1)).year(), boost::date_time::Jan, 1);
        if (rolledDate <= D2)
        {
            if (boost::gregorian::gregorian_calendar::is_leap_year((*yit).year()))
                y += (rolledDate - rolledD1).days()/366.;
            else
                y += (rolledDate - rolledD1).days()/365.;
            rolledD1 = rolledDate;
        }
        else
        {
            if (boost::gregorian::gregorian_calendar::is_leap_year((*yit).year()))
                y += (D2 - rolledD1).days()/366.;
            else
                y += (D2 - rolledD1).days()/365.;
            break;
        }
    }
    return y;
}
