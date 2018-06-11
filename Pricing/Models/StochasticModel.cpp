//
// Created by Alberto Campi on 01/05/2018.
//

#include "StochasticModel.h"

using namespace pricing;

const unsigned long StochasticModel::m_deltaT(1);

StochasticModel::StochasticModel(const math::RandomNumberGenerator &rng) : m_rngPtr(rng.clone()), m_optEventPtr(nullptr) {}

StochasticModel::StochasticModel(const math::RandomNumberGenerator &rng, const std::shared_ptr<pricing::OptionEvent> event) :
        m_rngPtr(rng.clone()), m_optEventPtr(event) {}
        
StochasticModel::StochasticModel(const pricing::StochasticModel &sourceModel) : 
        m_rngPtr(sourceModel.m_rngPtr -> clone()), m_optEventPtr(sourceModel.m_optEventPtr) {}
