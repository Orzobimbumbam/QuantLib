//
// Created by Alberto Campi on 01/05/2018.
//

#include "StochasticModel.h"

using namespace pricing;

StochasticModel::StochasticModel(const math::RandomNumberGenerator &rng) : m_rngPtr(rng.clone()) {}
