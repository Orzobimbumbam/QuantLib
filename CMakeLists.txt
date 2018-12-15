cmake_minimum_required(VERSION 3.10)
project(QuantLib)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
#find_package(Boost REQUIRED COMPONENTS unit_test_framework)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
#SET(GCC_COVERAGE_LINK_FLAGS "-coverage")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

include_directories(${Boost_INCLUDE_DIR})

add_executable(UTests BOOST.TESTS/UTests.cpp QuantLibIncludes.h)
target_include_directories(UTests PRIVATE ${BOOST_INCLUDE_DIRS})
#target_compile_options(UTests PRIVATE -fprofile-arcs -ftest-coverage)
target_link_libraries(UTests ${Boost_LIBRARIES} QuantLib)

add_custom_command(TARGET UTests PRE_BUILD COMMAND lcov --directory . --zerocounters)


add_library(QuantLib Pricing/PayOffSpecs/PayOff.cpp Pricing/PayOffSpecs/PayOff.h Pricing/PayOffSpecs/General/PayOffCall.cpp
        Pricing/PayOffSpecs/General/PayOffCall.h Pricing/PayOffSpecs/General/PayOffPut.cpp Pricing/PayOffSpecs/General/PayOffPut.h Math/Stat/Stat.cpp Math/Stat/Stat.h
        Math/Stat/StatOneDim.cpp Math/Stat/StatOneDim.h Math/math.h Pricing/OptionContracts/Option.cpp Pricing/OptionContracts/Option.h
        Common/DateUtils/DayCountConventionHelper.cpp Common/DateUtils/DayCountConventionHelper.h Common/Common.h
        Pricing/Pricing.h Pricing/PayOffSpecs/General/PayOffArithmeticAsianCall.cpp Pricing/PayOffSpecs/General/PayOffArithmeticAsianCall.h
        Common/DateUtils/OptionDate.cpp Common/DateUtils/OptionDate.h Pricing/PayOffSpecs/General/PayOffArithmeticAsianPut.cpp
        Pricing/PayOffSpecs/General/PayOffArithmeticAsianPut.h Pricing/Models/StochasticModels/StochasticModel.cpp Pricing/Models/StochasticModels/StochasticModel.h
        Pricing/Pricers/OptionPricer.cpp Pricing/Pricers/OptionPricer.h Pricing/Pricers/BlackScholesPricer.cpp
        Pricing/Pricers/BlackScholesPricer.h Math/math.cpp Pricing/Pricers/GeneralisedBlackScholesPricer.cpp
        Pricing/Pricers/GeneralisedBlackScholesPricer.h Common/Types/GeneralisedMarketDataType.cpp
        Common/Types/GeneralisedMarketDataType.h Common/Types/ParametricGeneralisedVolatility.cpp
        Common/Types/ParametricGeneralisedVolatility.h Common/Types/GeneralisedVolatility.cpp
        Common/Types/GeneralisedVolatility.h Common/Types/GeneralisedInterestRate.cpp
        Common/Types/GeneralisedInterestRate.h Common/Types/ShortRate.cpp Common/Types/ShortRate.h Pricing/Pricers/BlackPricer.cpp
        Pricing/Pricers/BlackPricer.h Common/Types/Numeraire.cpp Common/Types/Numeraire.h Common/Types/MoneyMarketAccountNumeraire.cpp
        Common/Types/MoneyMarketAccountNumeraire.h Pricing/Pricers/FXBlackScholesPricer.cpp Pricing/Pricers/FXBlackScholesPricer.h
        Math/RandomNumbers/BoxMuller.cpp Math/RandomNumbers/BoxMuller.hpp Math/RandomNumbers/RandomNumberGenerator.cpp
        Math/RandomNumbers/RandomNumberGenerator.h Math/RandomNumbers/BeasleySpringerMoro.cpp Math/RandomNumbers/BeasleySpringerMoro.h
        Pricing/Models/StochasticModels/General/GeometricBM.cpp Pricing/Models/StochasticModels/General/GeometricBM.h Pricing/Pricers/MonteCarloPricer.cpp
        Pricing/Pricers/MonteCarloPricer.h Pricing/PayOffSpecs/General/PayOffRangeAccrual.cpp Pricing/PayOffSpecs/General/PayOffRangeAccrual.h
        Common/Types/Range.cpp Common/Types/Range.h Math/RandomNumbers/Decorators/AntitheticSampling.cpp Math/RandomNumbers/Decorators/AntitheticSampling.h
        Pricing/OptionContracts/Extensions/OptionEvent.cpp Pricing/OptionContracts/Extensions/OptionEvent.h Pricing/OptionContracts/Extensions/KnockOutBarrierEvent.cpp
        Pricing/OptionContracts/Extensions/KnockOutBarrierEvent.h Pricing/OptionContracts/Extensions/DownKnockOutBarrierEvent.cpp
        Pricing/OptionContracts/Extensions/DownKnockOutBarrierEvent.h Pricing/OptionContracts/BarrierOption.cpp
        Pricing/OptionContracts/BarrierOption.h Pricing/OptionContracts/Extensions/UpKnockOutBarrierEvent.cpp
        Pricing/OptionContracts/Extensions/UpKnockOutBarrierEvent.h Pricing/OptionContracts/Extensions/KnockInBarrierEvent.cpp
        Pricing/OptionContracts/Extensions/KnockInBarrierEvent.h Pricing/OptionContracts/Extensions/UpKnockInBarrierEvent.cpp
        Pricing/OptionContracts/Extensions/UpKnockInBarrierEvent.h Pricing/OptionContracts/Extensions/DownKnockInBarrierEvent.cpp
        Pricing/OptionContracts/Extensions/DownKnockInBarrierEvent.h Pricing/Models/TreeModels/TreeModel.cpp Pricing/Models/TreeModels/TreeModel.h
        Pricing/Models/TreeModels/CoxRossRubinstein.cpp Pricing/Models/TreeModels/CoxRossRubinstein.h Pricing/Models/TreeModels/JarrowRudd.cpp
        Pricing/Models/TreeModels/JarrowRudd.h Pricing/OptionContracts/Extensions/BarrierEvent.cpp Pricing/OptionContracts/Extensions/BarrierEvent.h
        Pricing/Pricers/RecombiningTreePricer.cpp Pricing/Pricers/RecombiningTreePricer.h Pricing/Pricers/BinomialTreePricer.cpp Pricing/Pricers/BinomialTreePricer.h
        Pricing/OptionContracts/Extensions/EarlyExerciseEvent.cpp Pricing/OptionContracts/Extensions/EarlyExerciseEvent.h
        Pricing/FixedIncome/DiscountFactors/DiscountFactor.cpp Pricing/FixedIncome/DiscountFactors/DiscountFactor.h
        Pricing/FixedIncome/CurveBuilders/DiscountCurve.cpp Pricing/FixedIncome/CurveBuilders/DiscountCurve.h
        Pricing/FixedIncome/CurveBuilders/DiscountCurveBuilder.cpp Pricing/FixedIncome/CurveBuilders/DiscountCurveBuilder.h
        Math/InterpolationSchemes/Interpolator.cpp Math/InterpolationSchemes/Interpolator.h
        Math/InterpolationSchemes/LinearInterpolator.cpp Math/InterpolationSchemes/LinearInterpolator.h
        Pricing/FixedIncome/CurveBuilders/Wrappers/InterpolationSchemeWrapper.cpp Pricing/FixedIncome/CurveBuilders/Wrappers/InterpolationSchemeWrapper.h
        Pricing/FixedIncome/CurveBuilders/CurveBootstrapper.cpp Pricing/FixedIncome/CurveBuilders/CurveBootstrapper.h
        Math/InterpolationSchemes/NaturalCubicSplineInterpolator.cpp Math/InterpolationSchemes/NaturalCubicSplineInterpolator.h
        Common/IOUtils/IOUtils.cpp Common/IOUtils/IOUtils.hpp)