//
//  Pool.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Pool.hpp"
using namespace std;

Item* Pool::GetItemByIndex(unsigned int Index) { return &Content[Index]; }

void Pool::FillPool() {
    cout << "Content of the Pool nb " << this << "\n";
    for(int i = 0 ; i < NumItems; i++) {
        Content.push_back(Item(i, RandomVal(MAX_ITEM_VALUE), RandomVal(MAX_ITEM_VOLUME)));
    }
    cout << "\n";
}


Generation Pool::GenerateRandomBags(unsigned int N) {
    Generation G {};
    Mutation M;
    for(int BagIndex = 0; BagIndex < N; BagIndex++) {
        Bag Individual {};
        unsigned int NumberOfItems = RandomInt(MAX_NB_ITEMS_BAG, false);
        if(NumberOfItems <= 0) {
            throw "Problem";
        }
        for(int ItemIndex = 0; ItemIndex < NumberOfItems; ItemIndex++) {
            Individual.AddItem(GetItemByIndex(RandomVal(NumItems)));
        }
        M = { RandomVal(1.), RandomVal(1.), RandomVal(1.) };
        cout << M.AdditionProbability << ", " << M.SubstitutionProbability << ", " << M.SubstractionProbability << "\n";
        Individual.SetMutationType(M);
        G.AddBag(Individual);
    }
    return G;
}

Item* Pool::PickRandom() {
    return &Content[RandomVal((unsigned int)Content.size())];
}

void Pool::PrintContent() const {
    for (auto it = Content.begin(); it < Content.end(); it++) {
        it->PrintItem();
    }
}
