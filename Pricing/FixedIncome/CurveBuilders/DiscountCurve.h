//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_DISCOUNTCURVE_H
#define QUANTLIB_DISCOUNTCURVE_H

#include "../../pricing.h"
#include "DiscountCurveBuilder.h"
#include <memory>
#include <map>
#include <vector>

//class pricing::DiscountCurveBuilder;

class pricing::DiscountCurve
{
public:
    DiscountCurve(const pricing::DiscountCurveBuilder& curveBuilder);

    void buildDiscountCurve(const std::vector<double>& tenors);
    double getDiscountFactor(double tenor) const;

private:
    const std::unique_ptr<pricing::DiscountCurveBuilder> m_dcBuilderPtr;
    std::map<double, double> m_dc;

};


#endif //QUANTLIB_DISCOUNTCURVE_H
