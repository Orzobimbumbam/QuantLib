//
//  NormalRNGenClass.cpp
//  RandomNumbers
//
//  Created by Alberto Campi on 13/01/2017.
//  Copyright © 2017 Alberto Campi. All rights reserved.
//

#include "BoxMuller.hpp"
#include <cstdlib>

using namespace math;

BoxMuller::BoxMuller() : z2IsAvailable(false), z2(0) {}

double BoxMuller::generate()
{
    //check if z2 is still available from previous function call
    if (z2IsAvailable){
        z2IsAvailable = false;

        return z2;
    } else {
        //generate two new U(0,1] RV
        static std::mt19937 mtGen;//mersenne-twister rn gen
        const double u1 = (mtGen() + 0.5)/(static_cast<double>(mtGen.max()) + 1);
        const double u2 = (mtGen() + 0.5)/(static_cast<double>(mtGen.max()) + 1);

        //apply Box-Muller formula
        const double z1 = sqrt(-2*log(u1))*cos(2*boost::math::constants::pi<double>()*u2);
        z2 = sqrt(-2*log(u1))*sin(2*boost::math::constants::pi<double>()*u2);
        z2IsAvailable = true;

        return z1;
    }
}

std::unique_ptr<RandomNumberGenerator> BoxMuller::clone() const
{
    return std::make_unique<BoxMuller>(*this);
}













