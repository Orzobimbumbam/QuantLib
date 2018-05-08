cmake_minimum_required(VERSION 3.10)
project(QuantLib)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
#find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIR})

add_executable(UTests BOOST.TESTS/UTests.cpp QuantLibIncludes.h)
target_include_directories(UTests PRIVATE ${BOOST_INCLUDE_DIRS})
target_link_libraries(UTests ${Boost_LIBRARIES} QuantLib)


add_library(QuantLib Pricing/PayOffSpecs/PayOff.cpp Pricing/PayOffSpecs/PayOff.h Pricing/PayOffSpecs/General/PayOffCall.cpp
        Pricing/PayOffSpecs/General/PayOffCall.h Pricing/PayOffSpecs/General/PayOffPut.cpp Pricing/PayOffSpecs/General/PayOffPut.h Math/Stat/Stat.cpp Math/Stat/Stat.h
        Math/Stat/StatOneDim.cpp Math/Stat/StatOneDim.h Math/math.h Pricing/OptionContracts/Option.cpp Pricing/OptionContracts/Option.h
        Common/DateUtils/DayCountConventionHelper.cpp Common/DateUtils/DayCountConventionHelper.h Common/Common.h
        Pricing/Pricing.h Pricing/PayOffSpecs/General/PayOffArithmeticAsianCall.cpp Pricing/PayOffSpecs/General/PayOffArithmeticAsianCall.h
        Common/DateUtils/OptionDate.cpp Common/DateUtils/OptionDate.h Pricing/PayOffSpecs/General/PayOffArithmeticAsianPut.cpp
        Pricing/PayOffSpecs/General/PayOffArithmeticAsianPut.h Pricing/Models/StochasticModel.cpp Pricing/Models/StochasticModel.h
        Pricing/Pricers/OptionPricer.cpp Pricing/Pricers/OptionPricer.h Pricing/Pricers/BlackScholesPricer.cpp
        Pricing/Pricers/BlackScholesPricer.h Math/math.cpp Pricing/Pricers/GeneralisedBlackScholesPricer.cpp
        Pricing/Pricers/GeneralisedBlackScholesPricer.h Common/Types/GeneralisedMarketDataType.cpp
        Common/Types/GeneralisedMarketDataType.h Common/Types/ParametricGeneralisedVolatility.cpp
        Common/Types/ParametricGeneralisedVolatility.h Common/Types/GeneralisedVolatility.cpp
        Common/Types/GeneralisedVolatility.h Common/Types/GeneralisedInterestRate.cpp
        Common/Types/GeneralisedInterestRate.h Common/Types/ShortRate.cpp Common/Types/ShortRate.h Pricing/Pricers/BlackPricer.cpp
        Pricing/Pricers/BlackPricer.h Common/Types/Numeraire.cpp Common/Types/Numeraire.h Common/Types/MoneyMarketAccountNumeraire.cpp
        Common/Types/MoneyMarketAccountNumeraire.h Pricing/Pricers/FXBlackScholesPricer.cpp Pricing/Pricers/FXBlackScholesPricer.h)