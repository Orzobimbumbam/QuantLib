//
// Created by Alberto Campi on 20/07/2018.
//

#include "RecombiningTreePricer.h"

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                                                      const pricing::TreeModel &moveModel,
                                                      unsigned long nPeriods,
                                                      const pricing::OptionEvent &event) :
        m_optionStyle(optionStyle.clone()), m_optionPayOff(payOff.clone()),
        m_upMove(moveModel.getUpMove()), m_downMove(moveModel.getDownMove()), m_nPeriods(nPeriods), m_optionEvent(event.clone())
{
    checkPayOffType(*m_optionPayOff);
}

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                                                      const pricing::TreeModel &moveModel, unsigned long nPeriods) :
        m_optionStyle(optionStyle.clone()), m_optionPayOff(payOff.clone()),
        m_upMove(moveModel.getUpMove()), m_downMove(moveModel.getDownMove()), m_nPeriods(nPeriods), m_optionEvent(nullptr)
{
    checkPayOffType(*m_optionPayOff);
}

void pricing::RecombiningTreePricer::checkPayOffType(const pricing::PayOff &payOff) const
{
    if (payOff.isExoticPayOff())
        throw std::invalid_argument("pricing::RecombiningTreePricer : Invalid payoff type. \n"
                                    "recombining trees cannot price exotic payoffs.");

    else
        return;
}