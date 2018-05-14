//
// Created by Alberto Campi on 14/05/2018.
//

#include "BeasleySpringerMoro.h"

double math::BeasleySpringerMoro::generate() {
    static std::mt19937 mtGen;
    const double quantile = mtGen()/static_cast<double>(mtGen.max());

    return inverseNormCumulative(quantile);
}

double math::BeasleySpringerMoro::inverseNormCumulative(double quantile) const
{
    static double a[4] = {   2.50662823884,
                             -18.61500062529,
                             41.39119773534,
                             -25.44106049637};

    static double b[4] = {  -8.47351093090,
                            23.08336743743,
                            -21.06224101826,
                            3.13082909833};

    static double c[9] = {0.3374754822726147,
                          0.9761690190917186,
                          0.1607979714918209,
                          0.0276438810333863,
                          0.0038405729373609,
                          0.0003951896511919,
                          0.0000321767881768,
                          0.0000002888167364,
                          0.0000003960315187};

    if (quantile < 0 || quantile > 1)
        throw std::out_of_range("BeasleySpringerMoro::inverseNormCumulative : Invalid quantile value.");

    if (quantile >= 0.5 && quantile <= 0.92) {
        double num = 0.0;
        double denom = 1.0;

        for (int i=0; i<4; i++) {
            num += a[i] * pow((quantile - 0.5), 2*i + 1);
            denom += b[i] * pow((quantile - 0.5), 2*i);
        }
        return num/denom;

    } else if (quantile > 0.92 && quantile < 1) {
        double num = 0.0;

        for (int i=0; i<9; i++) {
            num += c[i] * pow((log(-log(1-quantile))), i);
        }
        return num;

    } else {
        return -1.0*inverseNormCumulative(1-quantile);
    }
}