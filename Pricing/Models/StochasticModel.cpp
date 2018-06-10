//
// Created by Alberto Campi on 01/05/2018.
//

#include "StochasticModel.h"

using namespace pricing;

const unsigned long StochasticModel::m_deltaT(1);

StochasticModel::StochasticModel(const math::RandomNumberGenerator &rng, const pricing::Option &optionStyle) : 
        m_rngPtr(rng.clone()), m_optPtr(optionStyle.clone()) {}
        
StochasticModel::StochasticModel(const pricing::StochasticModel &sourceModel) : 
        m_rngPtr(sourceModel.m_rngPtr -> clone()), m_optPtr(sourceModel.m_optPtr -> clone()) {}
        
const std::unique_ptr<pricing::Option>& StochasticModel::getOptionPtr() const 
{
    return m_optPtr;
}