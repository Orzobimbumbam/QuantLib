//
// Created by Alberto Campi on 11/11/2018.
//

#include "DiscountCurve.h"

pricing::DiscountCurve::DiscountCurve(const pricing::DiscountCurveBuilder &curveBuilder) :
        m_dcBuilderPtr(curveBuilder.clone()), m_dc() {}

void pricing::DiscountCurve::buildDiscountCurve(const std::vector<double> &tenors)
{
    m_dc = m_dcBuilderPtr -> buildDiscountCurve(tenors);
}

double pricing::DiscountCurve::getDiscountFactor(double tenor) const
{
    return m_dc.at(tenor);
}