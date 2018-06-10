//
// Created by Alberto Campi on 15/05/2018.
//

#ifndef QUANTLIB_GEOMETRICBM_H
#define QUANTLIB_GEOMETRICBM_H

#include "../StochasticModel.h"
#include "../../PayOffSpecs/PayOff.h"

class pricing::GeometricBM : public pricing::StochasticModel {
public:
    GeometricBM(const math::RandomNumberGenerator &rng, const pricing::Option &optionStyle, 
                double interestRate, double volatility, bool isExoticPayOff);

    PathMap SDE(double spot, const common::OptionDate &od) const override;
    virtual std::unique_ptr<pricing::StochasticModel> clone() const override;

private:
    const double m_ir, m_vol;
    const bool m_exoticFlag;

    void getExactSpotPath(PathMap& pm, double spot, const common::OptionDate &od, double deltaT) const;
    void getTerminalSpotValue(PathMap& pm, double spot, const common::OptionDate &od) const;
};


#endif //QUANTLIB_GEOMETRICBM_H
