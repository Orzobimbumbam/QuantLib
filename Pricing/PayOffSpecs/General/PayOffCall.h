//
// Created by Alberto Campi on 14/04/2018.
//

#ifndef QUANTLIB_PAYOFFCALL_H
#define QUANTLIB_PAYOFFCALL_H

#include "../PayOff.h"

class pricing::PayOffCall : public pricing::PayOff
{
public:
    explicit PayOffCall(double strike);
    PayOffCall(double strike, bool isPathDependent);
    double payOff(const PathMap& spot) const override;
    std::unique_ptr<PayOff> clone() const override;

private:
    const double m_strike;

};


#endif //QUANTLIB_PAYOFFCALL_H
