//
// Created by Alberto Campi on 11/11/2018.
//

#ifndef QUANTLIB_DISCOUNTCURVEBUILDER_H
#define QUANTLIB_DISCOUNTCURVEBUILDER_H

#include <map>
#include <vector>
#include <memory>

#include "../../pricing.h"
#include "../DiscountFactors/DiscountFactor.h"
#include "../../../Math/InterpolationSchemes/LinearInterpolator.h"
//#include "../../../Math/InterpolationSchemes/Interpolator.h"

class pricing::DiscountCurveBuilder
{
public:
    virtual std::map<double, double> buildDiscountCurve(const std::vector<double>& tenors) const = 0;
    virtual std::unique_ptr<pricing::DiscountCurveBuilder> clone() const = 0;

    virtual ~DiscountCurveBuilder() = default;
};


class pricing::DiscountCurveBuilderFromZero : public pricing::DiscountCurveBuilder
{
public:
    DiscountCurveBuilderFromZero(const std::map<double, double>& zeroCurve, const pricing::DiscountFactor& df);
    DiscountCurveBuilderFromZero(const DiscountCurveBuilderFromZero& rhs);

    std::map<double, double> buildDiscountCurve(const std::vector<double>& tenors) const override;
    std::unique_ptr<pricing::DiscountCurveBuilder> clone() const override;

private:
    const std::map<double, double> m_zeroCurve;
    const std::unique_ptr<pricing::DiscountFactor> m_dfPtr;
};


#endif //QUANTLIB_DISCOUNTCURVEBUILDER_H
