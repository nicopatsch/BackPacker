//
//  Utility.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Utility.hpp"


float Clamp(float Val, float min, float max) {
    if(Val <= min) return min;
    else if(Val >= max) return max;
    else return Val;
}


size_type RandomVal(const float Max) {
    return drand48()*Max;
}

int RandomInt(const int Max, bool AllowZeros) {
    if(AllowZeros) return rand() % Max;
    else return max(1, rand() % Max);
}

Mutation::Mutation(float Substrac, float Add, float Substit) {
    SubstractionProbability = Substrac;
    AdditionProbability = Add;
    SubstitutionProbability = Substit;
}


Mutation::Mutation() {
    Mutation(0.0, 0.0, 0.0);
}

void Mutation::Mutate() {
    if(RandomVal(1) < MutationProbability) MutateAddProb();
    if(RandomVal(1) < MutationProbability) MutateSubstracProb();
    if(RandomVal(1) < MutationProbability) MutateSubstitProb();
}

void Mutation::MutateAddProb() {
    float increment = RandomVal(2*MaxMutationIncrement) - MaxMutationIncrement;
    AdditionProbability = Clamp(AdditionProbability + increment, 0., 1.);
}

void Mutation::MutateSubstracProb() {
    float increment = RandomVal(2*MaxMutationIncrement) - MaxMutationIncrement;
    SubstractionProbability = Clamp(SubstractionProbability + increment, 0., 1.);
}

void Mutation::MutateSubstitProb() {
    float increment = RandomVal(2*MaxMutationIncrement) - MaxMutationIncrement;
     SubstitutionProbability = Clamp(SubstitutionProbability + increment, 0., 1.);
}
