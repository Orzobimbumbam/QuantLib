//
// Created by Alberto Campi on 06/07/2018.
//

#ifndef QUANTLIB_COXROSSRUBINSTEIN_H
#define QUANTLIB_COXROSSRUBINSTEIN_H


#include "TreeModel.h"

class pricing::CoxRossRubinstein : public pricing::TreeModel {
public:
    CoxRossRubinstein(double sigma, double expiry, unsigned long nSteps);

private:
    double upMove(double sigma, double expiry, unsigned long nSteps) const;

};


#endif //QUANTLIB_COXROSSRUBINSTEIN_H
