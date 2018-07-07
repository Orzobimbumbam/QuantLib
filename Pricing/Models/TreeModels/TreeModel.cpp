//
// Created by Alberto Campi on 06/07/2018.
//

#include "TreeModel.h"

pricing::TreeModel::TreeModel(double upMove, double downMove) : m_upMove(1 + upMove), m_downMove(1 - downMove) {}

double pricing::TreeModel::getUpMove() const
{
    return m_upMove;
}

double pricing::TreeModel::getDownMove() const
{
    return m_downMove;
}