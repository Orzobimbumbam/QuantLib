//
// Created by Alberto Campi on 06/07/2018.
//

#include "TreeModel.h"

pricing::TreeModel::TreeModel(double upMove, double downMove) : m_upMove(upMove), m_downMove(downMove) {}

double pricing::TreeModel::getUpMove() const
{
    return m_upMove;
}

double pricing::TreeModel::getDownMove() const
{
    return m_downMove;
}