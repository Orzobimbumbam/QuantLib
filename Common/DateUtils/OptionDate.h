//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_OPTIONDATE_H
#define QUANTLIB_OPTIONDATE_H


#include <boost/date_time/gregorian/greg_date.hpp>
#include "../Common.h"
#include "DayCountConventionHelper.h"

class common::OptionDate {

public:
    OptionDate(DayCountConventionInUse dcc, const boost::gregorian::date& maturityDate, const boost::gregorian::date& settlementDate,
                const boost::gregorian::date& todaysDate);

    boost::gregorian::date getMaturityDate() const;
    boost::gregorian::date getSettlementDate() const;
    boost::gregorian::date getTodaysDate() const;

    double getOptionYearsToMaturity() const;
    double getOptionYearsToSettlement() const;
    unsigned long getDaysToMaturity() const;
    unsigned long getDurationLengthInDays(double durationLengthInYears) const;

    DayCountConventionInUse getDayCountConventionInUse() const;

private:
    const boost::gregorian::date m_maturityDate, m_settlementDate, m_todaysDate;
    const double m_yearsToMaturity, m_yearsToSettlement;
    const DayCountConventionInUse m_dcc;
    OptionDate() = default;

    double _computeYears(DayCountConventionInUse dcc, const boost::gregorian::date& D2,
                                        const boost::gregorian::date& D1);

};


#endif //QUANTLIB_OPTIONDATE_H
