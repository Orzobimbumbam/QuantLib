//
// Created by Alberto Campi on 08/05/2018.
//

#include "FXBlackScholesPricer.h"

using namespace pricing;

FXBlackScholesPricer::FXBlackScholesPricer(double fxSpot, double vol, double domesticInterestRate,
                                           const common::OptionDate &dates, double strike, PutCallFlag pcf,
                                           double foreignInterestRate) :

        BlackScholesPricer(fxSpot, domesticInterestRate, vol, dates, strike, pcf, foreignInterestRate) {}