//
// Created by Alberto Campi on 01/05/2018.
//

#include "StochasticModel.h"

using namespace pricing;

const unsigned long StochasticModel::m_deltaT(1);

StochasticModel::StochasticModel(const math::RandomNumberGenerator &rng) : m_rngPtr(rng.clone()), m_optEventPtr(nullptr) {}

StochasticModel::StochasticModel(const math::RandomNumberGenerator &rng, const pricing::Option &optionStyle) :
        m_rngPtr(rng.clone()), m_optEventPtr(optionStyle.getOptionEvent()/* -> clone()*/) {}
        
StochasticModel::StochasticModel(const pricing::StochasticModel &sourceModel) : 
        m_rngPtr(sourceModel.m_rngPtr -> clone()),
        m_optEventPtr(sourceModel.m_optEventPtr)
{/*
    if (sourceModel.m_optEventPtr != nullptr)
        m_optEventPtr = sourceModel.m_optEventPtr -> clone();
        //m_optEventPtr = sourceModel.m_optEventPtr;

     else
         m_optEventPtr = nullptr;*/
}

void StochasticModel::resetOptionEventFlags() const
{
    if (m_optEventPtr != nullptr)
        m_optEventPtr -> resetAllFlags();
}