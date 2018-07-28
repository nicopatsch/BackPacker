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

class Generation {
    vector<Bag> Population;
    
public:
    Generation() : Population {} {}
    void PrintGenerationCompact();
    
    void PrintGenerationFull();
    
    void AddBag(Bag NewBag);
    
    unsigned long GetNbBags() const;
    
    Generation Select(const unsigned int MaxVolume, const unsigned int MaxNbBags);
    
    Generation Reproduce(Mutation MutationType);
    
};

#endif /* Generation_hpp */
