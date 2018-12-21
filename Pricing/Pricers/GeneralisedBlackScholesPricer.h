//
// Created by Alberto Campi on 02/05/2018.
//

#ifndef QUANTLIB_GENERALISEDBLACKSCHOLESPRICER_H
#define QUANTLIB_GENERALISEDBLACKSCHOLESPRICER_H

#include "BlackScholesPricer.h"
#include "../../Math/math.h"
#include "../../Common/Types/GeneralisedVolatility.h"
#include "../../Common/Types/GeneralisedInterestRate.h"

using namespace common;

//BSp on Equity index products - Div yield is either zero or continuously paid
//TODO derive class for single name equity products - Discrete Div yield

class pricing::GeneralisedBlackScholesPricer : public pricing::BlackScholesPricer
{
public:
    GeneralisedBlackScholesPricer(double spot, const GeneralisedVolatility& squaredVol, const GeneralisedInterestRate& interestRate,
                                  const common::OptionDate& dates, double strike, PutCallFlag pcf); //Dividend yield is assumed 0.

    double getRMSSquaredVolatility() const;
    double getAverageRate() const;

    //TODO: implement logic for integrating time-dependent deterministic dividend yields of given generic type e.g. GeneralisedDividendYield)


private:

};


#endif //QUANTLIB_GENERALISEDBLACKSCHOLESPRICER_H
