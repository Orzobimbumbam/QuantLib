//
// Created by Alberto Campi on 14/05/2018.
//

#ifndef QUANTLIB_BEASLEYSPRINGERMORO_H
#define QUANTLIB_BEASLEYSPRINGERMORO_H

#include "RandomNumberGenerator.h"

class math::BeasleySpringerMoro : public math::RandomNumberGenerator {
public:
    explicit BeasleySpringerMoro() = default;
    double generate() override;

    double inverseNormCumulative(double quantile) const;
};


#endif //QUANTLIB_BEASLEYSPRINGERMORO_H
