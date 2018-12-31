//
// Created by Alberto Campi on 15/04/2018.
//

#ifndef QUANTLIB_MATH_H
#define QUANTLIB_MATH_H

#include <iostream>
#include <cmath>
#include <boost/math/constants/constants.hpp>
#include <vector>
#include <set>
#include <limits>
#include <unordered_map>

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

    using NXW = std::unordered_map<unsigned long, std::vector<std::pair<double, double>>>;

    template <class T, double(T::*evaluate)(double) const, double(T::*fderivative)(double) const = nullptr> class NLSolver
    {
    public:
        explicit NLSolver(double accuracy): m_accuracy(accuracy), m_Nmax(1000) {}
        NLSolver(double accuracy, unsigned long maximumIterations): m_accuracy(accuracy), m_Nmax(maximumIterations)
        {
            if (maximumIterations <= 0)
            {
                m_Nmax = 1000;
                std::cerr << "W: math::NLSolverClass::NLSolver : maximum number of iterations must be a positive integer."
                             << std::endl << "Using default value..." << std::endl;
            }
        }

        void setMaximumIterations(unsigned long maximumIterations)
        {
            if (maximumIterations <= 0)
            {
                m_Nmax = 1000;
                std::cerr << "W: math::NLSolverClass::NLSolver : maximum number of iterations must be a positive integer."
                          << std::endl << "Using default value..." << std::endl;
            }
            else
                m_Nmax = maximumIterations;
        }

        void setAccuracy(double accuracy)
        {
            m_accuracy = accuracy;
        }

        double solveByBisection(const T& f, double targetValue, double a, double b) const //solver by bisection method
        {
            double y1 = (f.*evaluate)(a); //dereferencing a pointer to class method
            double y2 = (f.*evaluate)(b);

            if (std::abs(y1 - targetValue) <= m_accuracy)
                return y1;
            if (std::abs(y2 - targetValue) <= m_accuracy)
                return y2;
            if ((y1 - targetValue)*(y2 - targetValue) > 0)
                throw std::runtime_error("math::NLSolver::solveByBisection : No zeros in this interval.");

            unsigned long i = 0;
            double mid = a + 0.5*(b - a);
            double y = (f.*evaluate)(mid);

            while (std::abs(y - targetValue) >= m_accuracy)
            {
                if (i > m_Nmax) //avoid infinite loops
                {
                    std::cerr << "W: math::NLSolver::solveByBisection : accuracy could not be reached after "
                                 << i - 1 << " iterations." << std::endl
                                 << "Returning best estimate..." << std::endl;
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

        double solveByNewtonRaphson(const T& f, double targetValue, double x) const //solver by Newton-Raphson method
        {
            double y = (f.*evaluate)(x);
            long unsigned i = 0;
            while(std::abs(y - targetValue) >= m_accuracy)
            {
                double yprime = (f.*fderivative)(x);
                if (i > m_Nmax)
                {
                    std::cerr << "W: math::NLSolver::solveByNewtonRaphson : accuracy could not be reached after "
                              << i - 1 << " iterations." << std::endl
                              << "Returning best estimate..." << std::endl;
                    break;
                }
                if (yprime == 0)
                {
                    std::cerr << "E: math::NLSolver::solveByNewtonRaphson : function has zero derivative at " << x << std::endl;
                    throw std::runtime_error("E: math::NLSolver::solveByNewtonRaphson : algorithm failed to converge");
                }

                x = x - (y - targetValue)/yprime;
                y = (f.*evaluate)(x);
                ++i;
            }
            return x;
        }

    private:
        double m_accuracy;
        unsigned long m_Nmax;

    };

    class LegendrePolynomials
    {
    public:
        LegendrePolynomials();
        explicit LegendrePolynomials(unsigned long degree);

        void setDegree(unsigned long degree);

        double P(double x) const;
        double dP(double x) const;


    private:
        mutable double m_P, m_dP, m_x;
        unsigned long m_N;
        mutable bool m_areComputed;

        void _compute(double x) const;
    };

    class GaussLegendreIntegrationNXW
    {
    public:
        static NXW& get();

    private:
        static GaussLegendreIntegrationNXW* m_GLIPtr;
        NXW m_nxw;  //Nested hash table contains abscissa-weight (x, w) pairs keyed by Legendre polynomial degree (n) for fast re-use

        GaussLegendreIntegrationNXW() = default;
    };

    template <class T, double(T::*evaluate)(double) const> class NumQuadrature
    {
    public:
        NumQuadrature() : m_stepSize(0.01), m_maxRichardsonExtrapolations(100), m_maxGLIntervals(100000) {}
        explicit NumQuadrature(double stepSize) : m_stepSize(stepSize), m_maxRichardsonExtrapolations(100), m_maxGLIntervals(100000) {}

        void setStepSize(double h)
        {
            m_stepSize = h;
        }

        void setMaxRichardsonExtrapolations(unsigned long k)
        {
            m_maxRichardsonExtrapolations = k;
        }

        void setMaxGaussLegendreIntervals(unsigned long N)
        {
            if (N < 1)
            {
                m_maxGLIntervals = 100000;
                std::cerr << "W: math::NumQuadrature::setMaxGaussLegendreIntervals : maximum number of intervals must be a positive integer."
                             << std::endl << "Using default value..." << std::endl;
            }
            else
                m_maxGLIntervals = N;
        }

        double integrateByMidPoint(const T& integrand, const std::set<double>& mesh) const
        {
            double x = *mesh.begin(), integral = 0;
            for (auto it = ++mesh.begin(); it != mesh.end(); ++it)
            {
                const double midpoint = (x + *it)/2.;
                const double dx = *it - x;
                integral += (integrand.*evaluate)(midpoint)*dx;
                x = *it;
            }

            return integral;
        }

        double integrateByMidPoint(const T& integrand, double lowerEndpoint, double upperEndpoint) const
        {
            /*auto NSteps = static_cast<long>(std::abs(upperEndpoint - lowerEndpoint)/m_stepSize);
            double x = lowerEndpoint, integral = 0;
            for (unsigned long i = 0; i < NSteps; ++i)
            {
                const double midpoint = x + m_stepSize/2.;
                integral += (integrand.*evaluate)(midpoint);
                x += m_stepSize;
            }

            return integral*m_stepSize;*/
            std::set<double> mesh = _getMesh(lowerEndpoint, upperEndpoint);
            return integrateByMidPoint(integrand, mesh);
        }

        double integrateByTrapezoid(const T& integrand, const std::set<double>& mesh) const
        {
            double x = *mesh.begin(), integral = 0, fl = (integrand.*evaluate)(x), fu;
            for (auto  it = ++mesh.begin(); it != mesh.end(); ++it)
            {
                const double dx = *it - x;
                fu = (integrand.*evaluate)(*it);
                integral += (fu + fl)/2*dx;
                fl = fu;
                x = *it;
            }

            return  integral;
        }

        double integrateByTrapezoid(const T& integrand, double lowerEndpoint, double upperEndpoint) const
        {
            /*auto NSteps = static_cast<long>(std::abs(upperEndpoint - lowerEndpoint)/m_stepSize);
            const double endpointsEvaluation = ((integrand.*evaluate)(lowerEndpoint) +
                                               (integrand.*evaluate)(upperEndpoint))/2.;
            double x = lowerEndpoint + m_stepSize, integral = endpointsEvaluation;
            for (unsigned long i = 1; i < NSteps; ++i)
            {
                integral += (integrand.*evaluate)(x);
                x += m_stepSize;
            }

            return  integral*m_stepSize;*/
            std::set<double> mesh = _getMesh(lowerEndpoint, upperEndpoint);
            return integrateByTrapezoid(integrand, mesh);
        }

        double integrateBySimpson(const T& integrand, double lowerEndpoint, double upperEndpoint) const
        {
            auto NSteps = static_cast<long>(std::abs(upperEndpoint - lowerEndpoint)/m_stepSize);
            double integral = ((integrand.*evaluate)(lowerEndpoint) + (integrand.*evaluate)(upperEndpoint))/3;

            //check that the number of points is an even number
            if (NSteps%2 != 0)
                NSteps += 1; //if odd, increase by 1 and make it even

            double x = lowerEndpoint + m_stepSize;
            //weights for odd and even summation terms from Lagrange Polynomials expansion
            const double oddWeight = 4./3., evenWeight = 2./3.;
            for (unsigned long i = 1; i < NSteps; i++) {
                if (i%2 == 0)
                    integral += evenWeight*(integrand.*evaluate)(x);
                else integral += oddWeight*(integrand.*evaluate)(x);
                x += m_stepSize;
            }

            return integral*m_stepSize;
        }

        double integrateByAdaptiveRomberg(const T& integrand, double lowerEndpoint, double upperEndpoint, double tolerance) const
        {
            double h = std::abs(upperEndpoint - lowerEndpoint);
            std::vector<double> prevRow, thisRow;
            const double endpointsEvaluation = ((integrand.*evaluate)(lowerEndpoint) + (integrand.*evaluate)(upperEndpoint))/2.;
            double integral = endpointsEvaluation*h;
            prevRow.push_back(integral);
            double error = 0;

            long i = 0;
            //while (i <= m_maxRichardsonExtrapolations)
            do
            {
                ++i;
                if (i > m_maxRichardsonExtrapolations)
                {
                    std::cerr << "W: math::NumQuadrature::integrateByAdaptiveRomberg : maximum number of extrapolations exceeded with "
                                 "error: " << error << std::endl << "Returning best estimate..." << std::endl;
                    break;
                }

                integral = endpointsEvaluation;
                h = h/2;
                double x = lowerEndpoint;
                for (unsigned j = 1; j < pow(2, i); ++j)
                {
                    x += h;
                    integral += (integrand.*evaluate)(x);
                }

                integral *= h;
                thisRow.push_back(integral);

                for (unsigned j = 1; j <= i; ++j)
                {
                    const double powerFactor = pow(4, j);
                    integral = (powerFactor*thisRow[j-1] - prevRow[j-1])/(powerFactor -1); //Richardson's extrapolation
                    thisRow.push_back(integral);
                }

                error = std::abs(*thisRow.rbegin() - *prevRow.rbegin());
                prevRow = thisRow;
                thisRow.clear();

            } while (error >= tolerance);

            std::cerr << "math::NumQuadrature::integrateByAdaptiveRomberg : Convergence achieved after " << i << " iterations" << std::endl;
            return integral;
        }

        double integrateByGaussLegendre(const T& integrand, double lowerEndpoint, double upperEndpoint, double tolerance) const
        {
            double thisIntegral = 0, prevIntegral = std::numeric_limits<double>::max(), error = 0;
            unsigned long i = 1;
            LegendrePolynomials polys(i);

            do
            {
                if (i > m_maxGLIntervals)
                {
                    std::cerr << "W: math::NumQuadrature::integrateByGaussLegendre : maximum number of intervals exceeded with "
                                 "error: " << error << std::endl << "Returning best estimate..." << std::endl;
                    break;
                }

                thisIntegral = 0;

                //If no Legendre polynomial roots exists for the i-th degree, compute them
                if (GaussLegendreIntegrationNXW::get().find(i) == GaussLegendreIntegrationNXW::get().end())
                {
                    std::vector<std::pair<double, double>> xw;
                    //Use definite parity of Legendre polynomials to reduce number of roots to be computed
                    for (unsigned long j = 1; j <= int(i/2); ++j)   //Find roots only on positive semi-axis and use symmetry
                    {
                        const NLSolver<LegendrePolynomials, &LegendrePolynomials::P, &LegendrePolynomials::dP> solver(1e-6);
                        const double x0 = cos(
                                boost::math::constants::pi<double>() * (j - 1. / 4) / (i + 0.5));   //Initial guess goes anti-clockwise
                        const double x = solver.solveByNewtonRaphson(polys, 0, x0); //Only positive roots are found

                        const double dP = polys.dP(x);
                        const double w = 2 / ((1 - x * x) * dP * dP);   //Find weights as function of Legendre polynomial first derivative

                        xw.emplace_back(std::make_pair(x, w));

                        //Shift integral to [-1, 1] and evaluate at both positive and negative roots using Legendre polynomials symmetry
                        const double rescaledX = (upperEndpoint - lowerEndpoint) / 2. * x;
                        thisIntegral += w * ((integrand.*evaluate)(rescaledX + (upperEndpoint + lowerEndpoint) / 2.) +
                                             (integrand.*evaluate)(-rescaledX + (upperEndpoint + lowerEndpoint) / 2.));
                    }

                    //Odd polynomials always have a root at zero, no need to solve it numerically
                    if (i%2 != 0)
                    {
                        const double x = 0;
                        const double dP = polys.dP(x);
                        const double w = 2/(dP*dP);
                        xw.emplace_back(std::make_pair(x, w));
                        thisIntegral += w*(integrand.*evaluate)((upperEndpoint + lowerEndpoint)/2.);
                    }

                    //Store abscissas and weights as a collection of pairs
                    GaussLegendreIntegrationNXW::get().insert(std::make_pair(i, xw));

                }
                else    //If the roots already exist, use them
                {
                    for (unsigned long j = 0; j < (i%2 == 0 ? int(i/2) : int(i/2) + 1); ++j)
                    {
                        //Get previously computed roots and weights
                        const double x = GaussLegendreIntegrationNXW::get().at(i).at(j).first;
                        const double w = GaussLegendreIntegrationNXW::get().at(i).at(j).second;

                        //Shift integral to [-1, 1] and evaluate at both positive and negative roots using Legendre polynomials symmetry
                        const double rescaledX = (upperEndpoint - lowerEndpoint) / 2. * x;
                        thisIntegral += w * ((integrand.*evaluate)(rescaledX + (upperEndpoint + lowerEndpoint) / 2.) +
                                             (integrand.*evaluate)(-rescaledX + (upperEndpoint + lowerEndpoint) / 2.));
                    }
                }

                thisIntegral *= (upperEndpoint - lowerEndpoint)/2.;

                //Increment number of intervals and Legendre polynomial degree
                ++i;
                polys.setDegree(i);

                error = std::abs(thisIntegral - prevIntegral);
                prevIntegral = thisIntegral;

            } while (error >= tolerance);

            std::cerr << "math::NumQuadrature::integrateByGaussLegendre : Convergence achieved after " << i - 1 << " iterations" << std::endl;
            return thisIntegral;
        }


    private:
        double m_stepSize;
        unsigned long m_maxRichardsonExtrapolations;
        unsigned long m_maxGLIntervals;

        std::set<double> _getMesh(double a, double b) const
        {
            std::set<double> mesh;
            double x = a;
            mesh.insert(x);

            const auto NSteps = static_cast<long>(std::abs(b - a)/m_stepSize);
            for (unsigned long i = 0; i < NSteps; ++i)
            {
                x += m_stepSize;
                mesh.insert(x);
            }

            return mesh;
        }

    };

    double stdNormCdf(double x);
    double stdNormPdf(double x);

}


#endif //QUANTLIB_MATH_H
