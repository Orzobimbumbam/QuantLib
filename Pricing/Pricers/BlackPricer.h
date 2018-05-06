//
// Created by Alberto Campi on 06/05/2018.
//

#ifndef QUANTLIB_BLACKPRICER_H
#define QUANTLIB_BLACKPRICER_H

#include "../Pricing.h"
#include "OptionPricer.h"
#include "../../Common/Types/Numeraire.h"
#include "../../Common/DateUtils/OptionDate.h"


class pricing::BlackPricer : pricing::OptionPricer {
public:
    BlackPricer(double futureSpot, double rmsVol, const common::Numeraire&, const common::OptionDate& dates,
                double strike, PutCallFlag pcf);

    double optionPrice() const override;

private:
    const double m_futureSpot, m_rmsVol, m_strike, m_discountFactor;
    const short m_putCallFlag;
    const common::OptionDate m_od;

    double dPlusMinus(short plusMinusFlag) const;

};


#endif //QUANTLIB_BLACKPRICER_H
