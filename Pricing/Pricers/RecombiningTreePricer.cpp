//
// Created by Alberto Campi on 20/07/2018.
//

#include "RecombiningTreePricer.h"

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &optionStyle,
                                                      const pricing::TreeModel &moveModel,
                                                      const pricing::OptionEvent &event) :
        m_optionStyle(optionStyle.clone()), m_upMove(moveModel.getUpMove()),
        m_downMove(moveModel.getDownMove()), m_optionEvent(event.clone()), m_nPeriods(moveModel.getNPeriods())
{
    checkPayOffType(*m_optionStyle);
}

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &optionStyle,
                                                      const pricing::TreeModel &moveModel) :
        m_optionStyle(optionStyle.clone()), m_upMove(moveModel.getUpMove()),
        m_downMove(moveModel.getDownMove()), m_optionEvent(nullptr), m_nPeriods(moveModel.getNPeriods())
{
    checkPayOffType(*m_optionStyle);
}

void pricing::RecombiningTreePricer::checkPayOffType(const pricing::Option& ptionStyle) const
{
    if (m_optionStyle -> getOptionPayOffExoticFlag())
        throw std::invalid_argument("pricing::RecombiningTreePricer : Invalid payoff type. \n"
                                    "recombining trees cannot price exotic payoffs.");

    else
        return;
}