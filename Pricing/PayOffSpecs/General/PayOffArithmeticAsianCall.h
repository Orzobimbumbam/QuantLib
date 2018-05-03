//
// Created by Alberto Campi on 30/04/2018.
//

#ifndef QUANTLIB_PAYOFFARITHMETICASIANCALL_H
#define QUANTLIB_PAYOFFARITHMETICASIANCALL_H

#include <boost/date_time/gregorian/greg_date.hpp>
#include "../PayOff.h"

typedef std::vector<boost::gregorian::date> LookAtDateArray;

class pricing::PayOffArithmeticAsianCall : public pricing::PayOff
{
public:
    PayOffArithmeticAsianCall(double strike, const LookAtDateArray& lookAtDates);
    double payOff(const PathMap& dailySpot) const override;

    std::unique_ptr<PayOff> clone() const override;

private:
    const double m_strike;
    const LookAtDateArray m_lookAtDates;
};


#endif //QUANTLIB_PAYOFFARITHMETICASIANCALL_H
