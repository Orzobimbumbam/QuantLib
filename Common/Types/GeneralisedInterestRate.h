//
// Created by Alberto Campi on 03/05/2018.
//

#ifndef QUANTLIB_GENERALISEDINTERESTRATE_H
#define QUANTLIB_GENERALISEDINTERESTRATE_H

#include "GeneralisedMarketDataType.h"

using IRMap = std::map<double, double>;

class common::GeneralisedInterestRate : public GeneralisedMarketDataType
{
public:
    explicit GeneralisedInterestRate(const IRMap &data);
    explicit GeneralisedInterestRate(const std::map<boost::gregorian::date, double>& data, DayCountConventionInUse dcc);

    virtual double operator()(double t) const = 0;
    virtual double operator()(boost::gregorian::date t) const = 0;
    virtual std::map<double, double> get() const = 0;
    virtual long size() const = 0;

    virtual double getAverageRate() const;

protected:
    virtual double _getIntegrationStepSize() const = 0;

};


#endif //QUANTLIB_GENERALISEDINTERESTRATE_H
