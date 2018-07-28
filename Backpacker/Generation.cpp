//
//  Generation.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Generation.hpp"


void Generation::PrintGenerationCompact() {
    int SumValue = 0;
    int MaxValue = 0;
    
    for(auto BagIt = Population.begin(); BagIt<Population.end(); BagIt++) {
        BagIt->PrintPerformenceShort();
        if(MaxValue < BagIt->GetTotalValue()) MaxValue = BagIt->GetTotalValue();
        SumValue += BagIt->GetTotalValue();
    }
    cout << "\nMAX VALUE -> " << MaxValue << "\nAVERAGE VALUE -> " << SumValue/Population.size() << "\n\n";
}

void Generation::PrintGenerationFull() {
    for(auto BagIt = Population.begin(); BagIt<Population.end(); BagIt++) {
        BagIt->PrintContent();
        cout << " ----------------- \n";
    }
}

void Generation::AddBag(Bag NewBag) {
    Population.push_back(NewBag);
}

unsigned long Generation::GetNbBags() const {
    return Population.size();
    
}

Generation Generation::Select(const unsigned int MaxVolume, const unsigned int MaxNbBags) {
    
    sort(Population.begin(), Population.end(), [&](const Bag& LeftBag, const Bag& RightBag) {
        return LeftBag.GetTotalValue() > RightBag.GetTotalValue();
    });
    
    //Now that the bags are sorted in decreasing order of total value, we take the best ones.
    Generation BestBags {};
    
    unsigned int CurrBag = 0;
    while(BestBags.GetNbBags() < MaxNbBags && Population.size() > CurrBag) {
        if(Population[CurrBag].GetTotalVolume() <= MaxVolume) {
            BestBags.AddBag(Population[CurrBag]);
        }
        CurrBag++;
    }
    
    return BestBags;
}

Generation Generation::Reproduce(Mutation MutationType) {
    Generation NewGen {};
    Bag ChildBag {};
    for(auto Bag1It = Population.begin(); Bag1It < Population.end(); Bag1It++) {
        for(auto Bag2It = Population.begin(); Bag2It < Population.end(); Bag2It++) {
            ChildBag = Bag1It->Reproduce(*Bag2It, MutationType);
            NewGen.AddBag(ChildBag);
        }
    }
    return NewGen;
}


