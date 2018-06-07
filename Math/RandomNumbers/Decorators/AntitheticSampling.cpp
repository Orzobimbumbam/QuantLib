//
// Created by Alberto Campi on 07/06/2018.
//

#include "AntitheticSampling.h"

math::AntitheticSampling::AntitheticSampling(const math::RandomNumberGenerator &gen, unsigned long nPaths) :
                        m_rndGenPtr(gen.clone()), m_nAntitheticPaths(getEvenPaths(nPaths)), m_pathsCounter(0) {}

math::AntitheticSampling::AntitheticSampling(const math::AntitheticSampling &sourceSampling) :
                        m_rndGenPtr(sourceSampling.clone()),
                        m_nAntitheticPaths(sourceSampling.m_nAntitheticPaths),
                        m_pathsCounter(sourceSampling.m_pathsCounter) {}

double math::AntitheticSampling::generate()
{
    ++m_pathsCounter;
    double randomNumber;
    if (m_pathsCounter % 2 != 0)
    {
        randomNumber = m_rndGenPtr -> generate();
        m_antitheticNumber = -randomNumber;
    }
    else
        randomNumber = m_antitheticNumber;

    return randomNumber;
}

RandomArray math::AntitheticSampling::generateArray(unsigned long size)
{
    ++m_pathsCounter;
    RandomArray randArray;
    if (m_pathsCounter % 2 != 0)
    {
        randArray = m_rndGenPtr -> generateArray(size);
        for (const auto& it : randArray)
            m_antitheticArray.push_back(-it);
    }
    else
        randArray = m_antitheticArray;

    return randArray;
}

RandomMatrix math::AntitheticSampling::generateMatrix(unsigned long nRows, unsigned long nColums)
{
    ++m_pathsCounter;
    RandomMatrix randMatrix;
    if (m_pathsCounter % 2 != 0)
    {
        randMatrix = m_rndGenPtr -> generateMatrix(nRows, nColums);
        for (unsigned long i = 0; i < nRows; ++i)
            for (const auto& element : randMatrix[i])
                m_antitheticMatrix[i].push_back(-element);
    }
    else
        randMatrix = m_antitheticMatrix;

    return randMatrix;
}

std::unique_ptr<math::RandomNumberGenerator> math::AntitheticSampling::clone() const
{
    return std::make_unique<math::AntitheticSampling>(*this);
}

unsigned long math::AntitheticSampling::getEvenPaths(unsigned long nPaths) const
{
    if (nPaths % 2 == 0)
        return nPaths;
    else
        return nPaths + 1;
}

void math::AntitheticSampling::reset()
{
    m_antitheticArray.clear();
    m_antitheticMatrix.clear();
    m_antitheticNumber = 0;

    m_pathsCounter = 0;
}