//
// Created by Alberto Campi on 15/04/2018.
//

#ifndef QUANTLIB_MATH_H
#define QUANTLIB_MATH_H

#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>

namespace math
{
    class Stat;
    class StatOneDim;
    
    class RandomNumberGenerator;
    class BoxMuller;
    class BeasleySpringerMoro;
    class AntitheticSampling;

    class Interpolator;
    struct CSCoeffs;
    class LinearInterpolator;
    class NaturalCubicSplineInterpolator;
    
    
    template <class T, double(T::*evaluate)(double) const, double(T::*fderivative)(double) const = nullptr> class NLSolver
    {
    public:
        explicit NLSolver(double accuracy): m_accuracy(accuracy) {}

        double solveByBisection(const T& f, double targetValue, double a, double b) const //solver by bisection method
        {
            double y1 = (f.*evaluate)(a); //dereferencing a pointer to class method
            double y2 = (f.*evaluate)(b);

            if (std::abs(y1 - targetValue) <= m_accuracy)
                return y1;
            if (std::abs(y2 - targetValue) <= m_accuracy)
                return y2;
            if ((y1 - targetValue)*(y2 - targetValue) > 0)
                throw std::runtime_error("NLSolverClass: solveByBisection : No zeros in this interval.");

            const unsigned long Nmax = 1000;
            unsigned long i = 0;
            double mid = a + 0.5*(b - a);
            double y = (f.*evaluate)(mid);

            while (std::abs(y - targetValue) >= m_accuracy)
            {
                if (i == Nmax) //avoid infinite loops
                {
                    std::cerr << "NLSolverClass: solveByBisection : No zeros found." << std::endl;
                    break;
                }
                if ((y - targetValue)*((f.*evaluate)(a) - targetValue) < 0)
                    b = mid;
                else
                    a = mid;
                mid = a + 0.5*(b - a);
                y = (f.*evaluate)(mid);
                ++i;
            }
            return mid;
        }

        double solveByNR(const T& f, double targetValue, double x) const //solver by Newton-Raphson method
        {
            double y = (f.*evaluate)(x);

            const unsigned long Nmax = 1000;
            long unsigned i = 0;

            while(std::abs(y - targetValue) >= m_accuracy)
            {
                double yprime = (f.*fderivative)(x);
                if (i == Nmax || yprime == 0)
                {
                    std::cerr << "NLSolverClass: solveByNR : No zeros found." << std::endl;
                    break;
                }
                x = x - (y - targetValue)/yprime;
                y = (f.*evaluate)(x);
                ++i;
            }
            return x;
        }

    private:
        const double m_accuracy;

    };

    template <class T, double(T::*evaluate)(double) const> class NumQuadrature
    {
    public:
        explicit NumQuadrature(double stepSize) : m_stepSize(stepSize) {}

        double integrateByMidPoint(const T& integrand, double lowerEndpoint, double upperEndpoint) const
        {
            auto NSteps = static_cast<long>(std::abs(upperEndpoint - lowerEndpoint)/m_stepSize);
            double x = lowerEndpoint, integral = 0;
            for (unsigned long i = 0; i < NSteps; ++i)
            {
                const double midpoint = x + m_stepSize/2.;
                integral += (integrand.*evaluate)(midpoint);
                x += m_stepSize;
            }

            return integral*m_stepSize;
        }

        double integrateByTrapezoid(const T& integrand, double lowerEndpoint, double upperEndpoint) const
        {
            auto NSteps = static_cast<long>(std::abs(upperEndpoint - lowerEndpoint)/m_stepSize);
            const double endpointsEvaluation = ((integrand.*evaluate)(lowerEndpoint) +
                                               (integrand.*evaluate)(upperEndpoint))/2.;
            double x = lowerEndpoint + m_stepSize, integral = endpointsEvaluation;
            for (unsigned long i = 1; i < NSteps; ++i)
            {
                integral += (integrand.*evaluate)(x);
                x += m_stepSize;
            }

            return  integral*m_stepSize;
        }

        double integrateBySimpson(const T& integrand, double lowerEndpoint, double upperEndpoint) const
        {
            long numberOfPoints = static_cast<long>(std::abs(upperEndpoint - lowerEndpoint)/m_stepSize);
            double integral = ((integrand.*evaluate)(lowerEndpoint) + (integrand.*evaluate)(upperEndpoint))/3;

            //check that the number of points is an even number
            if (numberOfPoints%2 != 0)
                numberOfPoints += 1; //if odd, increase by 1 and make it even

            double x = lowerEndpoint + m_stepSize;
            //different weights for odd and even summation terms from Legendre Polynomials expansion
            const double oddWeight = 4./3., evenWeight = 2./3.;
            for (unsigned long i = 1; i < numberOfPoints; i++) {
                if (i%2 == 0)
                    integral += evenWeight*(integrand.*evaluate)(x);
                else integral += oddWeight*(integrand.*evaluate)(x);
                x += m_stepSize;
            }

            return integral*m_stepSize;
        }


    private:
        const double m_stepSize;
    };

    double stdNormCdf(double x);

    double stdNormPdf(double x);

}

#endif //QUANTLIB_MATH_H
