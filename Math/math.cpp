//
// Created by Alberto Campi on 01/05/2018.
//

#include "math.h"


double math::stdNormCdf(double x)
{
return (1 + std::erf(x/sqrt(2)))/2;
}

double math::stdNormPdf(double x)
{
    using namespace boost::math::constants;
    return 1./root_two_pi<double>()*exp(-x*x/2.);
}