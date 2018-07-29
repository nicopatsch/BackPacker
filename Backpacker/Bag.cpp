//
//  Bag.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Bag.hpp"
#include "Pool.hpp"
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
    Content.erase(Content.begin() + RandomVal(Content.size()));
}
void Bag::RandomAdd() {
    Content.push_back(Pool::GetInstance().PickRandom());
}
void Bag::RandomSubstitute() {
    int index = RandomVal(Content.size());
    Content[index] = Pool::GetInstance().PickRandom();
}

void Bag::Mutate(Mutation MutationType) {
    if(drand48() < MutationType.SubstractionProbability) {
        RandomSubstract();
    }
    if(drand48() < MutationType.AdditionProbability) {
        RandomAdd();
    }
    if(drand48() < MutationType.SubstitutionProbability) {
        RandomSubstitute();
    }
}

Bag Bag::Bag::Reproduce(Bag& Partner, Mutation MutationType) {
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
    ChildBag.Mutate(MutationType);
    return ChildBag;
}

