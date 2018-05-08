//
// Created by Alberto Campi on 01/05/2018.
//

#include "OptionDate.h"

common::OptionDate::OptionDate(DayCountConventionInUse dcc, const boost::gregorian::date &maturityDate,
                               const boost::gregorian::date &settlementDate, const boost::gregorian::date& todaysDate) :

        m_maturityDate(maturityDate), m_settlementDate(settlementDate), m_todaysDate(todaysDate),
        m_yearsToMaturity(computeYearsHelper(dcc, maturityDate, settlementDate)),
        m_yearsToSettlement(computeYearsHelper(dcc, settlementDate, todaysDate)) {}

boost::gregorian::date common::OptionDate::getMaturityDate() const
{
    return m_maturityDate;
}

boost::gregorian::date common::OptionDate::getSettlementDate() const
{
    return m_settlementDate;
}

double common::OptionDate::getOptionYearsToMaturity() const
{
    return m_yearsToMaturity;
}

double common::OptionDate::getOptionYearsToSettlement() const
{
    return m_yearsToSettlement;
}

double common::OptionDate::computeYearsHelper(DayCountConventionInUse dcc, const boost::gregorian::date &D2,
                                           const boost::gregorian::date &D1)
{
    common::DayCountConventionHelper dch(dcc);
    if (D2 >= D1)
        return dch.getAccrualPeriodInYears(D1, D2);
    else
        throw std::runtime_error("Option::Option : invalid date range.");
}