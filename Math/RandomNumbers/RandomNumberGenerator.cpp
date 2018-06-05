//
// Created by Alberto Campi on 14/05/2018.
//

#include "RandomNumberGenerator.h"

using namespace math;

std::mt19937 RandomNumberGenerator::mtGen;

RandomArray RandomNumberGenerator::generateArray(unsigned long size)
{
    RandomArray randomArray(size);
    for (unsigned long i = 0; i < randomArray.size(); ++i)
        randomArray[i] = generate();

    return randomArray;
}

RandomMatrix RandomNumberGenerator::generateMatrix(unsigned long nRows, unsigned long nColumns)
{
    RandomMatrix randomMatrix(nRows, std::vector<double>(nColumns));
    for (unsigned long i = 0; i < randomMatrix.size(); ++i)
    {
        for (unsigned long j = 0; j < nColumns; ++j)
            randomMatrix[i].push_back(generate());
    }

    return randomMatrix;
}
