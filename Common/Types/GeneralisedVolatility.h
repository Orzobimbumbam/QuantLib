//
// Created by Alberto Campi on 03/05/2018.
//

#ifndef QUANTLIB_GENERALISEDVOLATILITY_H
#define QUANTLIB_GENERALISEDVOLATILITY_H

#include "GeneralisedMarketDataType.h"
typedef std::map<double, double> VolMap;

class common::GeneralisedVolatility : public common::GeneralisedMarketDataType {
public:
    GeneralisedVolatility() = default;
    explicit GeneralisedVolatility(const VolMap &data);
    explicit GeneralisedVolatility(const std::map<boost::gregorian::date, double> &data, DayCountConventionInUse dcc);

    virtual double operator()(double t) const = 0;
    virtual double operator()(boost::gregorian::date t) const = 0;
    virtual VolMap get() const = 0;
    virtual long size() const = 0;

    virtual double getRMSSquaredVolatility() const;

protected:
    virtual double getIntegrationStepSize() const = 0;
};


#endif //QUANTLIB_GENERALISEDVOLATILITY_H
