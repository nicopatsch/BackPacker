//
//  Bag.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Bag_hpp
#define Bag_hpp

#include <stdio.h>
#include "Item.hpp"


class Bag {
    vector<Item*> Content;
    size_type TotalVolume;
    size_type TotalValue;
    
public:
    size_type GetTotalVolume() const;
    size_type GetTotalValue() const;
    unsigned long GetNumItems() const;
    Item* GetItemByIndex(unsigned int Index);
    Bag() : TotalVolume { }, TotalValue { }, Content { } { }
    void PrintContent() const;
    
    void PrintPerformence() const;
    void PrintPerformenceShort() const;
    
    void AddItem(Item* pObj);
    
    bool IsViable(int MaxVolume);
    void RandomSubstract();
    void RandomAdd();
    void RandomSubstitute();
    
    void Mutate(Mutation MutationType);
    
    Bag Reproduce(Bag& Partner, Mutation MutationType);
    
};


#endif /* Bag_hpp */
