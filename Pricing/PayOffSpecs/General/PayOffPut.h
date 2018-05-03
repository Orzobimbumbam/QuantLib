//
// Created by Alberto Campi on 14/04/2018.
//

#ifndef QUANTLIB_PAYOFFPUT_H
#define QUANTLIB_PAYOFFPUT_H

#include "../PayOff.h"

class pricing::PayOffPut : public pricing::PayOff
{
public:
    explicit PayOffPut(double strike);
    PayOffPut(double strike, bool isPathDependent);
    double payOff(const PathMap& spot) const override;
    std::unique_ptr<PayOff> clone() const override;

private:
    const double m_strike;

};


#endif //QUANTLIB_PAYOFFPUT_H
