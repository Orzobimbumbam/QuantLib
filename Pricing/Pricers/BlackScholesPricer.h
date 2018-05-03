//
// Created by Alberto Campi on 01/05/2018.
//

#ifndef QUANTLIB_BLACKSCHOLESPRICER_H
#define QUANTLIB_BLACKSCHOLESPRICER_H


#include "OptionPricer.h"
#include "../../Common/DateUtils/OptionDate.h"

enum PutCallFlag
{
    Call = 1,
    Put = -1
};

class pricing::BlackScholesPricer : public pricing::OptionPricer {
public:
    BlackScholesPricer(double spot, double vol, double interestRate, const common::OptionDate& dates, double strike, PutCallFlag pcf);

    double optionPrice() const override ;

protected:
    const double m_spot, m_vol, m_r, m_strike;
    const short m_putCallFlag;
    const common::OptionDate m_od;

    double dPlusMinus(short plusMinusFlag) const;
    //BlackScholesPricer();
private:
    //BlackScholesPricer();

};


#endif //QUANTLIB_BLACKSCHOLESPRICER_H
