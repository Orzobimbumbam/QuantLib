//
// Created by Alberto Campi on 12/06/2018.
//

#ifndef QUANTLIB_DOWNOUTBARRIEROPTION_H
#define QUANTLIB_DOWNOUTBARRIEROPTION_H


#include "Option.h"

class pricing::DownOutBarrierOption : public pricing::Option {
public:
    DownOutBarrierOption(const common::OptionDate& optionDate, const pricing::PayOff& optionPayOff,
            const pricing::DownKnockOutBarrierEvent& event);
    DownOutBarrierOption(const pricing::DownOutBarrierOption& sourceOption);

    double getOptionPayOff(const PathMap& spot) const final;

    std::unique_ptr<pricing::Option> clone() const override;


};


#endif //QUANTLIB_DOWNOUTBARRIEROPTION_H
