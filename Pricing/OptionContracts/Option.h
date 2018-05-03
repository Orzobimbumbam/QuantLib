//
// Created by Alberto Campi on 25/04/2018.
//

#ifndef QUANTLIB_OPTION_H
#define QUANTLIB_OPTION_H

#include <boost/date_time.hpp>
#include "../PayOffSpecs/PayOff.h"
#include "../../Common/Common.h"
#include "../../Common/DateUtils/OptionDate.h"

class pricing::Option
{
public:
    Option(const common::OptionDate& optionDate, const PayOff& optionPayOff);

    virtual double getOptionYearsToMaturity() const;
    virtual double getOptionPayOff(const PathMap& spot) const;

    ~Option() {};

protected:
    const std::unique_ptr<PayOff> m_optionPayOffType;
    const common::OptionDate m_optionDate;

private:

};

#endif //QUANTLIB_OPTION_H
