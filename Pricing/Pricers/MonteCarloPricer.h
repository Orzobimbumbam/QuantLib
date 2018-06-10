//
// Created by Alberto Campi on 03/06/2018.
//

#ifndef QUANTLIB_MONTECARLOPRICER_H
#define QUANTLIB_MONTECARLOPRICER_H


#include "OptionPricer.h"
#include "../OptionContracts/Option.h"
#include "../Models/StochasticModel.h"
#include "../../Common/Types/Numeraire.h"

class pricing::MonteCarloPricer : public pricing::OptionPricer {
public:
    MonteCarloPricer(const pricing::StochasticModel &model/*, const pricing::Option &option*/,
                     const common::Numeraire &numeraire, double spot, unsigned long nPaths);

    double optionPrice() const override;
    double stdError() const;
    void setPathNumber(unsigned long nPaths);

private:
    const std::unique_ptr<pricing::StochasticModel> m_mdl;
    //const std::unique_ptr<pricing::Option> m_option;
    const std::unique_ptr<common::Numeraire> m_numeraire;
    const double m_spot;
    mutable double m_stdError;
    unsigned long m_nPaths;

};


#endif //QUANTLIB_MONTECARLOPRICER_H
