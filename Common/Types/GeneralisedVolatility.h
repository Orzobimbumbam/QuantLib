//
// Created by Alberto Campi on 03/05/2018.
//

#ifndef QUANTLIB_GENERALISEDVOLATILITY_H
#define QUANTLIB_GENERALISEDVOLATILITY_H

#include "GeneralisedMarketDataType.h"
typedef std::map<double, double> VolMap;

class common::GeneralisedVolatility : public common::GeneralisedMarketDataType {
public:
    virtual double operator()(double t) const = 0;
    virtual std::map<double, double> get() const = 0;
    virtual long size() const = 0;

};


#endif //QUANTLIB_GENERALISEDVOLATILITY_H
