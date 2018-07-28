//
//  Item.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp


//--- Utility ---//
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Utility.hpp"



//--- Item Class ---//
class Item {
    unsigned int id;
    size_type Volume;
    size_type Value;
    
public:
    Item(unsigned int id_in, const size_type Volume_in, const size_type Value_in) : id { id_in }, Volume{ Volume_in }, Value{ Value_in } { }
    
    size_type GetVolume() const;
    size_type GetValue() const;
    void PrintItem() const;
    
};



#endif /* Item_hpp */
