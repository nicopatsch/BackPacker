//
//  Generation.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Generation_hpp
#define Generation_hpp

#include <stdio.h>
#include "Item.hpp"
#include "Bag.hpp"

struct GenerationStats { //Stats of one generation for history recording
    size_type MaxValue;
    size_type AverageValue;
    unsigned int MaxNbBags;
    float AverageNbBags;
    
    GenerationStats() {};
    GenerationStats(size_type MaxValue_in, size_type AverageValue_in, unsigned int MaxNbBags_in, float AverageNbBags_in) : MaxValue { MaxValue_in }, AverageValue { AverageValue_in }, MaxNbBags { MaxNbBags_in }, AverageNbBags { AverageNbBags_in } {}
};



class Generation {
    vector<Bag> Population;
    Mutation MutationType;
    
public:
    Generation();
    Generation(Mutation MutationType);
    void PrintGenerationCompact();
    GenerationStats GetGenerationStats();
    void PrintGenerationFull();
    
    void AddBag(Bag NewBag);
    
    unsigned long GetNbBags() const;
    
    Generation Select(const unsigned int MaxVolume, const unsigned int MaxNbBags);
    Generation Reproduce();
    void SetMutationType(Mutation MutationType_in);
    
    vector<Bag>& GetPopulation();
    void Absorb(Generation& OtherGen);
    
    pair<unsigned int, unsigned int> GetNbItemsPerBag();
    
};





#endif /* Generation_hpp */
