//
// Created by Alberto Campi on 20/07/2018.
//

#include "RecombiningTreePricer.h"

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &option,
                                                      const pricing::TreeModel &moveModel,
                                                      const pricing::OptionEvent &event) :
        m_option(option.clone()), m_upMove(moveModel.getUpMove()),
        m_downMove(moveModel.getDownMove()), m_optionEvent(event.clone()), m_nPeriods(moveModel.getNPeriods())
{
    checkPayOffType(*m_option);
}

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &option,
                                                      const pricing::TreeModel &moveModel) :
        m_option(option.clone()), m_upMove(moveModel.getUpMove()),
        m_downMove(moveModel.getDownMove()), m_optionEvent(nullptr), m_nPeriods(moveModel.getNPeriods())
{
    checkPayOffType(*m_option);
}

void pricing::RecombiningTreePricer::checkPayOffType(const pricing::Option& optionStyle) const
{
    if (m_option -> getOptionPayOffExoticFlag())
        throw std::invalid_argument("pricing::RecombiningTreePricer : Invalid payoff type. \n"
                                    "recombining trees cannot price exotic payoffs.");

    else
        return;
}

void pricing::RecombiningTreePricer::setMoveModel(const pricing::TreeModel &moveModel)
{
    m_upMove = moveModel.getUpMove();
    m_downMove = moveModel.getDownMove();
    m_nPeriods = moveModel.getNPeriods();
}

void pricing::RecombiningTreePricer::setOptionEvent(const pricing::OptionEvent &optionEvent)
{
    m_optionEvent = optionEvent.clone();
}