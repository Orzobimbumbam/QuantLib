//
// Created by Alberto Campi on 06/05/2018.
//

#ifndef QUANTLIB_MONEYMARKETACCOUNT_H
#define QUANTLIB_MONEYMARKETACCOUNT_H

#include "Numeraire.h"
#include "GeneralisedInterestRate.h"

class common::MoneyMarketAccount : public common::Numeraire {
public:
    explicit MoneyMarketAccount(const common::GeneralisedInterestRate& interestRate);
    explicit MoneyMarketAccount(double interestRate);

    double operator()(double T) const override;
    virtual std::unique_ptr<common::Numeraire> clone() const override;

private:
    const double m_ir;

};


#endif //QUANTLIB_MONEYMARKETACCOUNT_H
