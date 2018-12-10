//
// Created by Alberto Campi on 26/04/2018.
//

#ifndef QUANTLIB_PRICING_H
#define QUANTLIB_PRICING_H

namespace pricing
{
    class Option;
    class OptionEvent;
    class BarrierOption;

    class BarrierEvent;
    class KnockOutBarrierEvent;
    class DownKnockOutBarrierEvent;
    class UpKnockOutBarrierEvent;
    class KnockInBarrierEvent;
    class UpKnockInBarrierEvent;
    class DownKnockInBarrierEvent;
    class EarlyExerciseEvent;

    class PayOff;
    class PayOffCall;
    class PayOffPut;
    class PayOffArithmeticAsianCall;
    class PayOffArithmeticAsianPut;
    class PayOffRangeAccrual;

    class StochasticModel;
    class GeometricBM;

    class TreeModel;
    class CoxRossRubinstein;
    class JarrowRudd;

    class OptionPricer;
    class BlackScholesPricer;
    class GeneralisedBlackScholesPricer;
    class BlackPricer;
    class FXBlackScholesPricer;
    class MonteCarloPricer;
    class RecombiningTreePricer;
    class BinomialTreePricer;

    class DiscountFactor;
    class DiscountFactorLIBORRate;
    class DiscountFactorCompoundedRate;
    class DiscountFactorContinuouslyCompoundedRate;
    class DiscountCurve;
    class DiscountCurveBuilder;
    class DiscountCurveBuilderFromZero;
    class InterpolationSchemeWrapper;
    class CurveBootstrapper;
}

#endif //QUANTLIB_PRICING_H
