//
// Created by Alberto Campi on 04/05/2018.
//

#ifndef QUANTLIB_SHORTRATE_H
#define QUANTLIB_SHORTRATE_H

#include "GeneralisedInterestRate.h"

class common::ShortRate : public common::GeneralisedInterestRate {
public:
    ShortRate(const IRMap& shortRate, double h);

    double operator()(double t) const override;
    virtual double operator()(boost::gregorian::date t) const override ;
    IRMap get() const override;
    long size() const override;

protected:
    double getIntegrationStepSize() const override;

private:
    const double m_h;
};


#endif //QUANTLIB_SHORTRATE_H
