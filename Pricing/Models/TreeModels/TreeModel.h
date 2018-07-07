//
// Created by Alberto Campi on 06/07/2018.
//

#ifndef QUANTLIB_TREEMODEL_H
#define QUANTLIB_TREEMODEL_H

#include "../../Pricing.h"

class pricing::TreeModel {
public:
    TreeModel(double upMove, double downMove);

    virtual double getUpMove() const;
    virtual double getDownMove() const;

protected:
    TreeModel() = default;
    double m_upMove, m_downMove;
};


#endif //QUANTLIB_TREEMODEL_H
