//
// Created by Alberto Campi on 03/05/2018.
//

#ifndef QUANTLIB_GENERALISEDINTERESTRATE_H
#define QUANTLIB_GENERALISEDINTERESTRATE_H

#include "GeneralisedMarketDataType.h"

typedef std::map<double, double> IRMap;

class common::GeneralisedInterestRate : public GeneralisedMarketDataType {
public:
    GeneralisedInterestRate(const IRMap &data);

    virtual double operator()(double t) const = 0;
    virtual std::map<double, double> get() const = 0;
    virtual long size() const = 0;

    virtual double getAverageRate() const;

protected:
    virtual double getIntegrationStepSize() const = 0;

};


#endif //QUANTLIB_GENERALISEDINTERESTRATE_H
