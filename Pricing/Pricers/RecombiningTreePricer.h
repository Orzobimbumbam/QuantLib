//
// Created by Alberto Campi on 20/07/2018.
//

#ifndef QUANTLIB_RECOMBININGTREEPRICER_H
#define QUANTLIB_RECOMBININGTREEPRICER_H

#include <memory>
#include "OptionPricer.h"
#include "../Pricing.h"

class pricing::RecombiningTreePricer : public pricing::OptionPricer {
public:
    RecombiningTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                            const pricing::TreeModel &moveModel);

    RecombiningTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                          const pricing::TreeModel &moveModel, const pricing::OptionEvent &event);
    
    double optionPrice() const override;


protected:
    std::unique_ptr<pricing::Option> m_optionStyle;
    std::unique_ptr<pricing::PayOff> m_optionPayOff;
    std::unique_ptr<pricing::TreeModel> m_mdl;
    std::shared_ptr<pricing::OptionEvent> m_optionEvent;

    virtual double getSpotPriceAtNode(unsigned long stepIndex, unsigned long outcomeIndex) const = 0;
};


#endif //QUANTLIB_RECOMBININGTREEPRICER_H
