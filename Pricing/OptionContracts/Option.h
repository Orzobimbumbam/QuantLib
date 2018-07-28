//
// Created by Alberto Campi on 25/04/2018.
//

#ifndef QUANTLIB_OPTION_H
#define QUANTLIB_OPTION_H

#include <boost/date_time.hpp>
#include "../PayOffSpecs/PayOff.h"
#include "../../Common/Common.h"
#include "../../Common/DateUtils/OptionDate.h"
#include "Extensions/OptionEvent.h"

class pricing::Option //Encompasses all types of option styles but also gives freedom to derive from it
{
public:
    Option(const common::OptionDate& optionDate, const PayOff& optionPayOff);
    Option(const pricing::Option& sourceOption);
    Option(const common::OptionDate& optionDate, const PayOff& optionPayOff, const pricing::OptionEvent &event);
    //pricing::Option operator=(const pricing::Option &rhsOption);  //TODO: implement memory-safe copy assignment logic

    virtual double getOptionYearsToMaturity() const;
    virtual common::OptionDate getOptionDate() const;
    virtual double getOptionPayOff(const PathMap& spot) const;
    virtual bool getOptionPayOffExoticFlag() const;

    virtual std::unique_ptr<pricing::Option> clone() const;
    
    const std::shared_ptr<pricing::OptionEvent> getOptionEvent() const;

    ~Option() = default;

protected:
    const std::unique_ptr<pricing::PayOff> m_optionPayOffType;
    const common::OptionDate m_optionDate;
    const std::shared_ptr<pricing::OptionEvent> m_optEventPtr;

private:

};

#endif //QUANTLIB_OPTION_H
