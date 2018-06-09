//
// Created by Alberto Campi on 07/06/2018.
//

#ifndef QUANTLIB_ANTITHETICSAMPLING_H
#define QUANTLIB_ANTITHETICSAMPLING_H

#include "../RandomNumberGenerator.h"


class math::AntitheticSampling : public math::RandomNumberGenerator {
public:
    AntitheticSampling(const math::RandomNumberGenerator& gen, unsigned long nPaths);
    AntitheticSampling(const math::AntitheticSampling& sourceSampling);

    double generate() final;
    RandomArray generateArray(unsigned long size) final;
    RandomMatrix generateMatrix(unsigned long nRows, unsigned long nColumns) final;

    void reset();

    std::unique_ptr<RandomNumberGenerator> clone() const override;

private:
    const std::unique_ptr<math::RandomNumberGenerator> m_rndGenPtr;
    const unsigned long m_nAntitheticPaths;
    unsigned long m_pathsCounter;

    double m_antitheticNumber;
    RandomArray m_antitheticArray;
    RandomMatrix m_antitheticMatrix;

    unsigned long getEvenPaths(unsigned long nPaths) const;
};


#endif //QUANTLIB_ANTITHETICSAMPLING_H
