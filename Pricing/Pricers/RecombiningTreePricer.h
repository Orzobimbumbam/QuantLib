//
// Created by Alberto Campi on 20/07/2018.
//

#ifndef QUANTLIB_RECOMBININGTREEPRICER_H
#define QUANTLIB_RECOMBININGTREEPRICER_H

#include <memory>
#include "OptionPricer.h"
#include "../Pricing.h"
#include "../OptionContracts/Option.h"
#include "../PayOffSpecs/PayOff.h"
#include "../Models/TreeModels/TreeModel.h"
#include "../OptionContracts/Extensions/OptionEvent.h"

//Use only for Vanilla (non-path-dependent) payoffs

class pricing::RecombiningTreePricer : public pricing::OptionPricer {
public:
    RecombiningTreePricer(const pricing::Option &option,
                          const pricing::TreeModel &moveModel);

    RecombiningTreePricer(const pricing::Option &option,
                          const pricing::TreeModel &moveModel,
                          const pricing::OptionEvent &event);
    
    double optionPrice() const override = 0;

    void setMoveModel(const pricing::TreeModel &moveModel);
    void setOptionEvent(const pricing::OptionEvent &optionEvent);

protected:
    const std::unique_ptr<pricing::Option> m_option;
    std::shared_ptr<pricing::OptionEvent> m_optionEvent;

    double m_upMove, m_downMove;
    unsigned long m_nPeriods;

    virtual double getSpotPriceAtNode(unsigned long stepIndex, unsigned long outcomeIndex) const = 0;

private:
    void checkPayOffType(const pricing::Option& optionStyle) const;
};


#endif //QUANTLIB_RECOMBININGTREEPRICER_H
