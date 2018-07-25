//
// Created by Alberto Campi on 21/07/2018.
//

#ifndef QUANTLIB_BINOMIALTREEPRICER_H
#define QUANTLIB_BINOMIALTREEPRICER_H


#include "RecombiningTreePricer.h"
#include "../../Common/Types/MoneyMarketAccountNumeraire.h"

class pricing::BinomialTreePricer : public pricing::RecombiningTreePricer {
public:
    BinomialTreePricer(const pricing::Option &optionStyle, const pricing::TreeModel &moveModel,
                       double spot, const common::MoneyMarketAccount &discountCurve);

    BinomialTreePricer(const pricing::Option &optionStyle, const pricing::TreeModel &moveModel,
                       const pricing::OptionEvent &event, double spot, const common::MoneyMarketAccount &discountCurve);

    double optionPrice() const override;

private:
    double m_spot, m_tau;
    common::MoneyMarketAccount m_mma;

    bool isArbitrage() const;
    double getRiskNeutralProbUpMove() const;
    double getSpotPriceAtNode(unsigned long stepIndex, unsigned long outcomeIndex) const override;
};


#endif //QUANTLIB_BINOMIALTREEPRICER_H
