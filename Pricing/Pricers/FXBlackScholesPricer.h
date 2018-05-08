//
// Created by Alberto Campi on 08/05/2018.
//

#ifndef QUANTLIB_FXBLACKSCHOLESPRICER_H
#define QUANTLIB_FXBLACKSCHOLESPRICER_H

#include "BlackScholesPricer.h"

class pricing::FXBlackScholesPricer : public pricing::BlackScholesPricer {
public:
    FXBlackScholesPricer(double fxSpot, double vol, double domesticInterestRate, const common::OptionDate &dates,
                         double strike, PutCallFlag pcf, double foreignInterestRate); //force initialisation of m_divYield,
    // replaced by foreignInterestRate

};


#endif //QUANTLIB_FXBLACKSCHOLESPRICER_H
