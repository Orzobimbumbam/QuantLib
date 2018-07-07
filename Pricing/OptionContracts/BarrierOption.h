//
// Created by Alberto Campi on 12/06/2018.
//

#ifndef QUANTLIB_DOWNOUTBARRIEROPTION_H
#define QUANTLIB_DOWNOUTBARRIEROPTION_H


#include "Option.h"

class pricing::BarrierOption : public pricing::Option {
public:
    BarrierOption(const common::OptionDate& optionDate, const pricing::PayOff& optionPayOff,
            const pricing::BarrierEvent& event);
    BarrierOption(const pricing::BarrierOption& sourceOption);

    double getOptionPayOff(const PathMap& spot) const final;
    //void setBarrierEventType(const pricing::OptionEvent& event);

    std::unique_ptr<pricing::Option> clone() const override;


};


#endif //QUANTLIB_DOWNOUTBARRIEROPTION_H
