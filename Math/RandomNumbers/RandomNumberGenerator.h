//
// Created by Alberto Campi on 14/05/2018.
//

#ifndef QUANTLIB_RANDOMNUMBERGENERATOR_H
#define QUANTLIB_RANDOMNUMBERGENERATOR_H

#include <vector>
#include <cmath>
#include <random>
#include "../math.h"

typedef std::vector<std::vector<double>> RandomMatrix;
typedef std::vector<double> RandomArray;

class math::RandomNumberGenerator {
public:
    virtual double generate() = 0;
    virtual RandomArray generateArray(unsigned long size);
    virtual RandomMatrix generateMatrix(unsigned long nRows, unsigned long nColums);

    virtual std::unique_ptr<math::RandomNumberGenerator> clone() const = 0;

    virtual ~RandomNumberGenerator() = default;

protected:
    static std::mt19937 mtGen;

};


#endif //QUANTLIB_RANDOMNUMBERGENERATOR_H
