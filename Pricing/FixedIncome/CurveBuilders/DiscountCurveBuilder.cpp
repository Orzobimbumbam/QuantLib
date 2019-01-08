//
// Created by Alberto Campi on 11/11/2018.
//

#include "DiscountCurveBuilder.h"
#include "../../../Math/InterpolationSchemes/NaturalCubicSplineInterpolator.h"

pricing::DiscountCurveBuilder::DiscountCurveBuilder(const std::map<double, double> &inputCurve) :
        m_inputCurve(inputCurve) {}

pricing::DiscountCurveBuilderFromZero::DiscountCurveBuilderFromZero(const std::map<double, double> &zeroCurve,
                                                                    const pricing::DiscountFactor &df,
                                                                    const math::Interpolator &interpolationScheme) :
        DiscountCurveBuilder(zeroCurve), m_dfPtr(df.clone()), m_interpPtr(interpolationScheme.clone()) {}

pricing::DiscountCurveBuilderFromZero::DiscountCurveBuilderFromZero(const std::map<double, double> &zeroCurve,
                                                                    const pricing::DiscountFactor &df) :
        DiscountCurveBuilder(zeroCurve), m_dfPtr(df.clone()), m_interpPtr(new math::NaturalCubicSplineInterpolator()) {}

pricing::DiscountCurveBuilderFromZero::DiscountCurveBuilderFromZero(const pricing::DiscountCurveBuilderFromZero &rhs) :
        DiscountCurveBuilder(rhs.m_inputCurve), m_dfPtr(rhs.m_dfPtr -> clone()) {}

std::unique_ptr<pricing::DiscountCurveBuilder> pricing::DiscountCurveBuilderFromZero::clone() const
{
    return std::make_unique<pricing::DiscountCurveBuilderFromZero>(*this);
}

std::map<double, double> pricing::DiscountCurveBuilderFromZero::buildDiscountCurve(const std::set<double> &tenors) const
{
    std::map<double, double> discountCurve(m_inputCurve);
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


pricing::DiscountCurveBuilderFromBootstrap::DiscountCurveBuilderFromBootstrap(const std::map<double, double>& inputCurve,
                                                                              const pricing::CurveBootstrapper &bootstrapper) :
        DiscountCurveBuilder(inputCurve), m_bts(bootstrapper) {}

std::map<double, double> pricing::DiscountCurveBuilderFromBootstrap::buildDiscountCurve(const std::set<double> &tenors) const
{
    return m_bts.getBootstrappedCurves(m_inputCurve, tenors).discountCurve;
}

std::unique_ptr<pricing::DiscountCurveBuilder> pricing::DiscountCurveBuilderFromBootstrap::clone() const
{
    return std::make_unique<pricing::DiscountCurveBuilderFromBootstrap>(*this);
}