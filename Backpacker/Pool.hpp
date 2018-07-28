//
//  Pool.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Pool_hpp
#define Pool_hpp

#include <stdio.h>
#include "Generation.hpp"
#include "Item.hpp"

class Pool {
    std::vector<Item> Content;
    const unsigned int NumItems;
    void FillPool();
    
    Pool(unsigned int NumItems_in) : NumItems { NumItems_in } {
        FillPool();
    }
    
public:
    static Pool &GetInstance() {
        static Pool ThePoolSingleton { NB_ITEMS_IN_POOL };
        return ThePoolSingleton;
    }
    
    Item* GetItemByIndex(unsigned int Index);
    Generation GenerateRandomBags(unsigned int N);
    
    Item* PickRandom();
    void PrintContent() const;
    
};




#endif /* Pool_hpp */
