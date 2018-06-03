//
// Created by Alberto Campi on 06/05/2018.
//

#ifndef QUANTLIB_NUMERAIRE_H
#define QUANTLIB_NUMERAIRE_H

#include <memory>
#include "../Common.h"

class common::Numeraire {
public:
    virtual double operator()(double T) const = 0;
    virtual std::unique_ptr<common::Numeraire> clone() const = 0;

    virtual ~Numeraire() = default;

};


#endif //QUANTLIB_NUMERAIRE_H
