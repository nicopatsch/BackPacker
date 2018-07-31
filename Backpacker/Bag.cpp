//
//  Bag.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Bag.hpp"
#include "Pool.hpp"
#include <algorithm>
using namespace std;


size_type Bag::GetTotalVolume() const {
    return TotalVolume;
    
}

size_type Bag::GetTotalValue() const {
    return TotalValue;
    
}

unsigned long Bag::GetNumItems() const {
    return Content.size();
    
}

Item* Bag::GetItemByIndex(unsigned int Index) {
    return Content[Index];

}

void Bag::PrintContent() const {
    cout << "Content of the Bag nb " << this << "\n";
    for (auto it = Content.begin(); it < Content.end(); it++) {
        (*it)->PrintItem();
    }
    cout << "\nTotal Value : " << GetTotalValue() << "\nTotal Volume : " << GetTotalVolume() << "\n";
}

void Bag::PrintPerformence() const {
    cout << "Performence of the Bag nb " << this;
    cout << " : " << GetNumItems() << " objects for a total value of " << GetTotalValue() << ", total volume of " << GetTotalVolume() << "\n";
}
void Bag::PrintPerformenceShort() const {
    cout << "Bag nb " << this;
    cout << " : " << GetNumItems() << " objects, TValue : " << GetTotalValue() << ", TVolume : " << GetTotalVolume() << "\n";
}

void Bag::AddItem(Item* pObj) {
    if(Content.size() < MAX_NB_ITEMS_BAG) {
        Content.push_back(pObj);
        TotalVolume += pObj->GetVolume();
        TotalValue += pObj->GetValue();
    }
}

bool Bag::IsViable(int MaxVolume) {
    return TotalVolume <= MaxVolume;
    
}

void Bag::RandomSubstract() {
    if(Content.size() > 1) {
        Content.erase(Content.begin() + RandomInt((int)Content.size()));
    }
}
void Bag::RandomAdd() {
    Item* pNewItem = Pool::GetInstance().PickRandom();
    //While the item is already in the bag, take another one
    while(find(Content.begin(), Content.end(), pNewItem) != Content.end()) {
        pNewItem = Pool::GetInstance().PickRandom();
    }
    Content.push_back(pNewItem);
}
void Bag::RandomSubstitute() {
    int index = RandomInt((int)Content.size());
    Item* pNewItem = Pool::GetInstance().PickRandom();
    //While the item is already in the bag, take another one
    while(find(Content.begin(), Content.end(), pNewItem) != Content.end()) {
        pNewItem = Pool::GetInstance().PickRandom();
    }
    Content[index] = pNewItem;
}

void Bag::Mutate() {
    if(RandomVal(1) < MutationType.SubstractionProbability) {
        RandomSubstract();
    }
    if(RandomVal(1) < MutationType.AdditionProbability) {
        RandomAdd();
    }
    if(RandomVal(1) < MutationType.SubstitutionProbability) {
        RandomSubstitute();
    }
    MutationType.Mutate();
}

void Bag::SetMutationType(Mutation MutationType_in) {
    MutationType = MutationType_in;
}

Mutation Bag::GetMutationType() {
    return MutationType;
}

Bag Bag::Reproduce(Bag& Partner) {
    Bag ChildBag;
    int CurrItem = 0;
    while(this->GetNumItems() > CurrItem || Partner.GetNumItems() > CurrItem) {
        if(CurrItem % 2 == 0 && this->GetNumItems() > CurrItem) {
            ChildBag.AddItem(this->GetItemByIndex(CurrItem));
        }
        else if(CurrItem % 2 == 1 && Partner.GetNumItems() > CurrItem) {
            ChildBag.AddItem(Partner.GetItemByIndex(CurrItem));
        }
        CurrItem++;
    }
    
    //We inherit the mutation type of only one of the parents, not an average of the 2, orelse we will completely lose the benefits of that specific value of the mutation type.
    ChildBag.SetMutationType(MutationType);
    ChildBag.Mutate();
    return ChildBag;
}

