//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_DISCOUNTCURVEBUILDER_H
#define QUANTLIB_DISCOUNTCURVEBUILDER_H

#include <map>
#include <vector>
#include <memory>
#include <set>

#include "../../pricing.h"
#include "../DiscountFactors/DiscountFactor.h"
#include "../../../Math/InterpolationSchemes/LinearInterpolator.h"
#include "CurveBootstrapper.h"

namespace math  //forward declaration must be inside the correct namespace
{
    class Interpolator;
}

namespace pricing
{
    class CurveBootstrapper;
}

class pricing::DiscountCurveBuilder
{
public:
    DiscountCurveBuilder(const std::map<double, double>& inputCurve);
    virtual std::map<double, double> buildDiscountCurve(const std::set<double>& tenors) const = 0;
    virtual std::unique_ptr<pricing::DiscountCurveBuilder> clone() const = 0;

    virtual ~DiscountCurveBuilder() = default;

protected:
    std::map<double, double> m_inputCurve;
};


class pricing::DiscountCurveBuilderFromZero : public pricing::DiscountCurveBuilder
{
public:
    DiscountCurveBuilderFromZero(const std::map<double, double>& zeroCurve, const pricing::DiscountFactor& df);
    DiscountCurveBuilderFromZero(const std::map<double, double>& zeroCurve, const pricing::DiscountFactor& df,
                                 const math::Interpolator& interpolationScheme);

    DiscountCurveBuilderFromZero(const DiscountCurveBuilderFromZero& rhs);

    std::map<double, double> buildDiscountCurve(const std::set<double>& tenors) const override;
    std::unique_ptr<pricing::DiscountCurveBuilder> clone() const override;

private:
    const std::unique_ptr<pricing::DiscountFactor> m_dfPtr;
    const std::unique_ptr<math::Interpolator> m_interpPtr;
};


class pricing::DiscountCurveBuilderFromBootstrap : public pricing::DiscountCurveBuilder
{
public:
    DiscountCurveBuilderFromBootstrap(const std::map<double, double>& inputCurve, const pricing::CurveBootstrapper& bootstrapper);

    std::map<double, double> buildDiscountCurve(const std::set<double>& tenors) const override;
    std::unique_ptr<pricing::DiscountCurveBuilder> clone() const override;
    
private:
    const pricing::CurveBootstrapper m_bts;
};


#endif //QUANTLIB_DISCOUNTCURVEBUILDER_H
