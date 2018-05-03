//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_PAYOFFARITHMETICASIANPUT_H
#define QUANTLIB_PAYOFFARITHMETICASIANPUT_H

#include <boost/date_time/gregorian/greg_date.hpp>
#include "../PayOff.h"

typedef std::vector<boost::gregorian::date> LookAtDateArray;


class pricing::PayOffArithmeticAsianPut : public pricing::PayOff
{
public:
    PayOffArithmeticAsianPut(double strike, const LookAtDateArray& lookAtDates);
    double payOff(const PathMap& dailySpot) const override;

    std::unique_ptr<PayOff> clone() const override;

private:
    const double m_strike;
    const LookAtDateArray m_lookAtDates;
};


#endif //QUANTLIB_PAYOFFARITHMETICASIANPUT_H
