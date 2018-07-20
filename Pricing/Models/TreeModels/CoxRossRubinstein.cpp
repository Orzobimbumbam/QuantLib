//
// Created by Alberto Campi on 06/07/2018.
//

#include "CoxRossRubinstein.h"
#include <cmath>

pricing::CoxRossRubinstein::CoxRossRubinstein(double sigma, double expiry, unsigned long nSteps) :
        TreeModel(upMove(sigma, expiry, nSteps), 1./upMove(sigma, expiry, nSteps))
{
    //m_upMove = upMove(sigma, expiry, nSteps);
    //m_downMove = 1./m_upMove;
}

double pricing::CoxRossRubinstein::upMove(double sigma, double expiry, unsigned long nSteps) const
{
    return exp(sigma*sqrt(expiry/nSteps));
}

std::unique_ptr<pricing::TreeModel> pricing::CoxRossRubinstein::clone() const
{
    return std::make_unique<pricing::CoxRossRubinstein>(*this);
}