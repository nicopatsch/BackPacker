//
//  Item.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Item.hpp"
using namespace std;

size_type Item::GetVolume() const {
    return Volume;
    
}
size_type Item::GetValue() const {
    return Value;
    
}
void Item::PrintItem() const {
    cout << "Item number " << id << " -> Volume : " << Volume << " ; Value " << Value << "\n";
}

