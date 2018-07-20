//
// Created by Alberto Campi on 06/07/2018.
//

#include "JarrowRudd.h"
#include <cmath>

pricing::JarrowRudd::JarrowRudd(double sigma, double r, double expiry, unsigned long nSteps) :
        TreeModel(upMove(sigma, r, expiry, nSteps), downMove(sigma, r, expiry, nSteps))
{
    //m_upMove = upMove(sigma, r, expiry, nSteps);
    //m_downMove = downMove(sigma, r, expiry, nSteps);
}

double pricing::JarrowRudd::upMove(double sigma, double r, double expiry, unsigned long nSteps) const
{
    const double tau = expiry/nSteps;
    return exp((r - sigma*sigma/2)*tau + sigma*sqrt(tau));
}

double pricing::JarrowRudd::downMove(double sigma, double r, double expiry, unsigned long nSteps) const
{
    const double tau = expiry/nSteps;
    return exp((r - sigma*sigma/2)*tau - sigma*sqrt(tau));
}

std::unique_ptr<pricing::TreeModel> pricing::JarrowRudd::clone() const
{
    return std::make_unique<pricing::JarrowRudd>(*this);
}