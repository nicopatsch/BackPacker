//
//  Island.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 29/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Island_hpp
#define Island_hpp

#include <stdio.h>
#include "Generation.hpp"
#include <string.h>


class Island {
    Generation CurrentGen;
    unsigned int MaxVolume;
    unsigned int NbBagsPerGen;
    vector<GenerationStats> History;
    
public:
    Island(unsigned int MaxVolume, unsigned NbBagsPerGen, Mutation MutationType);
    void Absorb(Island& OtherIsland);
    
    void PrintIslandHistory(string FileName);
    
    void DevelopDuring(unsigned int NbGenerations);
    void EmptyIsland();
    Generation& GetCurrentGen();
};



#endif /* Island_hpp */
