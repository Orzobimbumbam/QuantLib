//
// Created by Alberto Campi on 03/05/2018.
//

#ifndef QUANTLIB_PARAMETRICGENERALISEDVOLATILITY_H
#define QUANTLIB_PARAMETRICGENERALISEDVOLATILITY_H

#include "GeneralisedVolatility.h"

class common::ParametricGeneralisedVolatility : public common::GeneralisedVolatility {
public:
    ParametricGeneralisedVolatility(const common::OptionDate& dates, double a, double b, double c, double d);

    double operator()(double t) const override;
    double operator()(boost::gregorian::date t) const override;
    VolMap get() const override;
    long size() const override;

    double getParametricSquaredVolatility(double t) const; //return squared vol : maybe should be private?
    void setOLSParams(double a, double b, double c, double d);

protected:
    double getIntegrationStepSize() const override;

private:
    const long m_size;
    double m_a, m_b, m_c, m_d, m_yearsToMaturity;

    std::map<boost::gregorian::date, double> getDateMap(const common::OptionDate& dates) const;
    long getSize(const common::OptionDate& dates) const;
    //void getData();
};


#endif //QUANTLIB_PARAMETRICGENERALISEDVOLATILITY_H
