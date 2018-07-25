//
// Created by Alberto Campi on 06/07/2018.
//

#ifndef QUANTLIB_TREEMODEL_H
#define QUANTLIB_TREEMODEL_H

#include <memory>
#include "../../Pricing.h"

class pricing::TreeModel {
public:
    TreeModel(double upMove, double downMove, unsigned long nSteps);

    virtual double getUpMove() const;
    virtual double getDownMove() const;

    virtual std::unique_ptr<pricing::TreeModel> clone() const = 0;
    virtual unsigned long getNPeriods() const;
    
    virtual ~TreeModel() = default;

protected:
    double m_upMove, m_downMove; //TODO: store m_nPeriods and make a virtual function return it!!
    unsigned long m_nSteps;
};


#endif //QUANTLIB_TREEMODEL_H
