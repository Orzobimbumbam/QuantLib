//
// Created by Alberto Campi on 20/07/2018.
//

#include "RecombiningTreePricer.h"
#include "../OptionContracts/Option.h"
#include "../PayOffSpecs/PayOff.h"
#include "../Models/TreeModels/TreeModel.h"
#include "../OptionContracts/Extensions/OptionEvent.h"

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                                                      const pricing::TreeModel &moveModel,
                                                      const pricing::OptionEvent & event) :
        m_optionStyle(optionStyle.clone()), m_optionPayOff(payOff.clone()),
        m_mdl(moveModel.clone()), m_optionEvent(event.clone()) {}

pricing::RecombiningTreePricer::RecombiningTreePricer(const pricing::Option &optionStyle, const pricing::PayOff &payOff,
                                                      const pricing::TreeModel &moveModel) :
        m_optionStyle(optionStyle.clone()), m_optionPayOff(payOff.clone()), m_mdl(moveModel.clone()) {}