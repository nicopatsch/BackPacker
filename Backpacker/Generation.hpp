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
    size_type StdVarValue;
    
    unsigned int MaxNbItemsPerBag;
    float AverageNbItemsPerBag;
    float StdVarNbItemsPerBag;
    
    Mutation MaxMutationType;
    Mutation AverageMutationType;
    
    GenerationStats() {};
    GenerationStats(size_type MaxValue_in,
                    size_type AverageValue_in,
                    size_type StdVarValue_in,
                    unsigned int MaxNbItemsPerBag_in,
                    float AverageNbItemsPerBag_in,
                    float StdVarNbItemsPerBag_in,
                    Mutation MaxMutationType_in,
                    Mutation AverageMutationType_in):
    MaxValue { MaxValue_in },
    AverageValue { AverageValue_in },
    StdVarValue { StdVarValue_in },
    MaxNbItemsPerBag { MaxNbItemsPerBag_in },
    AverageNbItemsPerBag { AverageNbItemsPerBag_in },
    StdVarNbItemsPerBag { StdVarNbItemsPerBag_in },
    MaxMutationType { MaxMutationType_in },
    AverageMutationType { AverageMutationType_in } {}
};



class Generation {
    vector<Bag> Population;
    //Mutation MutationType; REMOVE
    
public:
    Generation();
    //Generation(Mutation MutationType); REMOVE
    void PrintGenerationCompact();
    GenerationStats GetGenerationStats();
    void PrintGenerationFull();
    
    void AddBag(Bag NewBag);
    
    unsigned long GetNbBags() const;
    
    Generation Select(const unsigned int MaxVolume, const unsigned int MaxNbBags);
    Generation Reproduce();
    Generation Reproduce(int FirstIndex, int SecondIndex);
    //void SetMutationType(Mutation MutationType_in); REMOVE
    
    vector<Bag>& GetPopulation();
    void Absorb(Generation& OtherGen);
    Generation InterGenerationReproduce(Generation& OtherGen, int FirstIndex, int SecondIndex);
    Generation InterGenerationReproduceMix(Generation& OtherGen);
        
    pair<unsigned int, unsigned int> GetNbItemsPerBag();
    
};





#endif /* Generation_hpp */
