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
    MonteCarloPricer(const pricing::StochasticModel &model, const pricing::Option &option,
                     const common::Numeraire &numeraire, double spot, unsigned long nPaths);

    double optionPrice() const override;
    double stdError() const;

    void setPathNumber(unsigned long nPaths);
    void setSpot(double spot);
    void setOption(const pricing::Option &option);
    void setModel(const pricing::StochasticModel &model);
    void setNumeraire(const common::Numeraire &numeraire);

private:
    std::unique_ptr<pricing::StochasticModel> m_mdl;
    std::unique_ptr<pricing::Option> m_option;
    std::unique_ptr<common::Numeraire> m_numeraire;
    double m_spot;
    mutable double m_stdError;
    unsigned long m_nPaths;

};


#endif //QUANTLIB_MONTECARLOPRICER_H
