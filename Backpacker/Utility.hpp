//
//  Utility.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Utility_hpp
#define Utility_hpp

#include <stdio.h>

#include <iostream>
#include <vector>
#include <math.h>
#include <memory.h>

using namespace std;
using size_type = float;
const unsigned int MAX_NB_ITEMS_BAG = 100; //The maximum number of objects a bag can contain
const unsigned int MAX_ITEM_VALUE = 100;
const unsigned int MAX_ITEM_VOLUME = 100;
const unsigned int NB_ITEMS_IN_POOL = 500;

size_type RandomVal(const float Max);
int RandomInt(const int Max, bool AllowZeros = false);

struct Mutation {
    static constexpr float MaxMutationIncrement = 0.1;
    static constexpr float MutationProbability = 0.05;
    
    float SubstractionProbability;
    float AdditionProbability;
    float SubstitutionProbability;
    Mutation(float Substrac, float Add, float Substit);
    Mutation();
    
    void Mutate();
    
    void MutateAddProb();
    void MutateSubstracProb();
    void MutateSubstitProb();
    
    
    friend std::ostream& operator<<(std::ostream& os, const Mutation& TheMutation)
    {
        // write out individual members of s with an end of line between each one
        os << TheMutation.AdditionProbability<< '\n';
        os << TheMutation.SubstractionProbability << '\n';
        os << TheMutation.SubstitutionProbability;
        
        return os;
    }
    
    // Extraction operator
    friend std::istream& operator>>(std::istream& is, Mutation& TheMutation)
    {
        // read in individual members of s
        is >> TheMutation.AdditionProbability >> TheMutation.SubstractionProbability >> TheMutation.SubstitutionProbability;
        return is;
    }
};


#endif /* Utility_hpp */
