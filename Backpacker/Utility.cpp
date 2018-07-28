//
//  Utility.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Utility.hpp"

size_type RandomVal(const int Max) {
    return drand48()*Max;
}

Mutation::Mutation(float Substrac, float Add, float Substit) {
    SubstractionProbability = Substrac;
    AdditionProbability = Add;
    SubstitutionProbability = Substit;
}
