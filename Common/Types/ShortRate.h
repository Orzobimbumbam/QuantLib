//
// Created by Alberto Campi on 04/05/2018.
//

#ifndef QUANTLIB_SHORTRATE_H
#define QUANTLIB_SHORTRATE_H

#include "GeneralisedInterestRate.h"

class common::ShortRate : public common::GeneralisedInterestRate
{
public:
    ShortRate(const IRMap& shortRate);
    ShortRate(const std::map<boost::gregorian::date, double>& data, DayCountConventionInUse dcc);

    double operator()(double t) const override;
    double operator()(boost::gregorian::date t) const override;
    IRMap get() const override;
    long size() const override;

protected:
    //double _getIntegrationStepSize() const override;

private:
    //const double m_h;
    //double getH(const std::map<boost::gregorian::date, double>& data, DayCountConventionInUse dcc) const;
};


#endif //QUANTLIB_SHORTRATE_H
