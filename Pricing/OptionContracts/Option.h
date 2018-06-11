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

class pricing::Option //European style option type
{
public:
    Option(const common::OptionDate& optionDate, const PayOff& optionPayOff);
    Option(const pricing::Option& sourceOption);
    //pricing::Option operator=(const pricing::Option &rhsOption);  //TODO: implement memory-safe copy assignment logic

    virtual double getOptionYearsToMaturity() const;
    virtual common::OptionDate getOptionDate() const;
    virtual double getOptionPayOff(const PathMap& spot) const;

    virtual std::unique_ptr<pricing::Option> clone() const;
    
    std::shared_ptr<pricing::OptionEvent> getOptionEvent() const;

    ~Option() = default;

protected:
    std::unique_ptr<pricing::PayOff> m_optionPayOffType;
    common::OptionDate m_optionDate;
    
    std::shared_ptr<pricing::OptionEvent> m_optEventPtr;


private:

};

#endif //QUANTLIB_OPTION_H
