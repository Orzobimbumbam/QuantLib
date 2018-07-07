//
// Created by Alberto Campi on 06/07/2018.
//

#ifndef QUANTLIB_JARROWRUDD_H
#define QUANTLIB_JARROWRUDD_H


#include "TreeModel.h"

class pricing::JarrowRudd : public pricing::TreeModel {
public:
    JarrowRudd(double sigma, double r, double expiry, unsigned long nSteps);

private:
    double upMove(double sigma, double r, double expiry, unsigned long nSteps) const;
    double downMove(double sigma, double r, double expiry, unsigned long nSteps) const;

};


#endif //QUANTLIB_JARROWRUDD_H
