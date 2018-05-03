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

class pricing::GeneralisedBlackScholesPricer : public pricing::BlackScholesPricer
{
public:
    GeneralisedBlackScholesPricer(double spot, const GeneralisedVolatility& squaredVol, const GeneralisedInterestRate& interestRate,
                                  const common::OptionDate& dates, double strike, PutCallFlag pcf, double h);


private:

    //VolMap getSquaredVol(const GeneralisedVolatility& vol) const;
    double getRMSVol(const GeneralisedMarketDataType& squaredVol, double ytm) const;
    double getAvgRate(const GeneralisedMarketDataType& interestRate, double ytm) const;
};


#endif //QUANTLIB_GENERALISEDBLACKSCHOLESPRICER_H
