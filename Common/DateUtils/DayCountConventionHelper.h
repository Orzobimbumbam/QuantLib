//
// Created by Alberto Campi on 25/04/2018.
//

#ifndef QUANTLIB_DAYCOUNTCONVENTIONHELPER_H
#define QUANTLIB_DAYCOUNTCONVENTIONHELPER_H

#include <boost/date_time.hpp>
#include <string>
#include "../Common.h"

enum DayCountConventionInUse //add more daycount conventions here
{
    Simple,
    Act_Act,
    Thirty_ThreeSixty,
    Thirty_ThreeSixtyFive,
    Thirty_TwoFiftyTwo
};

class common::DayCountConventionHelper
{
public:
    DayCountConventionHelper(DayCountConventionInUse dcc);

    double getLengthInYears(const boost::gregorian::date& startDate,
                                   const boost::gregorian::date& endDate) const;
    unsigned long getLengthInDays(double lengthInYears) const;

private:
    int m_daysInMonth, m_daysInYear;
    bool m_isActual;

    void _dayCountConventionMapper(DayCountConventionInUse dcc);
    double _getLengthInYearsNoActual(const boost::gregorian::date& D1,
                                           const boost::gregorian::date& D2) const;

    double _getLengthInYearsActual(const boost::gregorian::date& D1,
                                         const boost::gregorian::date& D2) const;
};


#endif //QUANTLIB_DAYCOUNTCONVENTIONHELPER_H
