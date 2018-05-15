//
//  NormalRNGenClass.hpp
//  RandomNumbers
//
//  Created by Alberto Campi on 13/01/2017.
//  Copyright © 2017 Alberto Campi. All rights reserved.
//

#ifndef BoxMuller_hpp
#define BoxMuller_hpp

#include "RandomNumberGenerator.h"


//const double PI = 3.14159265359;

class math::BoxMuller : public math::RandomNumberGenerator {
public:
    BoxMuller();
    double generate() override;

    std::unique_ptr<RandomNumberGenerator> clone() const override;

private:
    bool z2IsAvailable;
    double z2;
    
};

#endif
