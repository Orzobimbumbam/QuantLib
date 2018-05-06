//
// Created by Alberto Campi on 06/05/2018.
//

#include "MoneyMarketAccountNumeraire.h"

common::MoneyMarketAccount::MoneyMarketAccount(double interestRate) : m_ir(interestRate) {}
common::MoneyMarketAccount::MoneyMarketAccount(const common::GeneralisedInterestRate &interestRate) :
m_ir(interestRate.getAverageRate()) {}

double common::MoneyMarketAccount::operator()(double T) const {
    return exp(-m_ir*T);
}
