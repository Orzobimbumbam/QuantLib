//
// Created by Alberto Campi on 02/05/2018.
//

#ifndef QUANTLIB_GENERALISEDMARKETDATATYPE_H
#define QUANTLIB_GENERALISEDMARKETDATATYPE_H

#include "../Common.h"
#include "../DateUtils/OptionDate.h"
#include <map>

class common::GeneralisedMarketDataType {
public:
    GeneralisedMarketDataType() = default;
    GeneralisedMarketDataType(const std::map<double, double> &data);

    virtual double operator()(double t) const = 0;
    virtual std::map<double, double> get() const = 0;
    virtual long size() const = 0;

    virtual ~GeneralisedMarketDataType() = default;

protected:
    std::map<double, double> m_data;
};


#endif //QUANTLIB_GENERALISEDMARKETDATATYPE_H
