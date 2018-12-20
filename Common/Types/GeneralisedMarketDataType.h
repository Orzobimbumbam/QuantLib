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
    GeneralisedMarketDataType(const std::map<boost::gregorian::date, double> &data, DayCountConventionInUse dcc);

    virtual double operator()(double t) const = 0;
    virtual double operator()(boost::gregorian::date t) const = 0;
    virtual std::map<double, double> get() const = 0;
    //virtual std::map<boost::gregorian::date, double> get() = 0;
    virtual long size() const = 0;

    virtual ~GeneralisedMarketDataType() = default;

protected:
    std::map<double, double> m_data;

    std::map<boost::gregorian::date, double> m_dateDoubleMap; //stores dates as key and years as values (doubles)
    virtual void _dateToDoubleMapper(const std::map<boost::gregorian::date, double> &data, DayCountConventionInUse dcc);
    //virtual void doubleToDateMapper(const std::map<double, double> &data);
};


#endif //QUANTLIB_GENERALISEDMARKETDATATYPE_H
