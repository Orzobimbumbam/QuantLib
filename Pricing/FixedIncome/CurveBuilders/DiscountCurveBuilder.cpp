//
// Created by Alberto Campi on 11/11/2018.
//

#include "DiscountCurveBuilder.h"

pricing::DiscountCurveBuilderFromZero::DiscountCurveBuilderFromZero(const std::map<double, double> &zeroCurve,
                                                                    const pricing::DiscountFactor &df) :
    m_zeroCurve(zeroCurve), m_dfPtr(df.clone()) {}

pricing::DiscountCurveBuilderFromZero::DiscountCurveBuilderFromZero(const pricing::DiscountCurveBuilderFromZero &rhs) :
    m_zeroCurve(rhs.m_zeroCurve), m_dfPtr(rhs.m_dfPtr -> clone()) {}

std::unique_ptr<pricing::DiscountCurveBuilder> pricing::DiscountCurveBuilderFromZero::clone() const
{
    return std::make_unique<pricing::DiscountCurveBuilderFromZero>(*this);
}

std::map<double, double> pricing::DiscountCurveBuilderFromZero::buildDiscountCurve(const std::vector<double> &tenors) const
{
    std::map<double, double> discountCurve(m_zeroCurve);
    for (auto& it : tenors)
    {
        if (discountCurve.find(it) == discountCurve.end())
        {
            math::LinearInterpolator linInterp;
            linInterp.interpolate(discountCurve, it);
        }
        else
        {
            discountCurve.insert(std::make_pair(it, m_dfPtr -> getDiscountFactor(it, discountCurve.at(it))));
        }
    }
    return discountCurve;
}