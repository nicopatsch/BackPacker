//
//  Island.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 29/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Island.hpp"
#include "Pool.hpp"
#include <fstream>
#include <iostream>


Island::Island(unsigned int MaxVolume_in, unsigned NbBagsPerGen_in, Mutation MutationType) : MaxVolume { MaxVolume_in }, NbBagsPerGen { NbBagsPerGen_in } {
    CurrentGen = Pool::GetInstance().GenerateRandomBags(NbBagsPerGen_in);
    Pool::GetInstance().PrintContent();
    CurrentGen.SetMutationType(MutationType);
}

void Island::Merge(Island& OtherIsland) {
    CurrentGen.Absorb(OtherIsland.GetCurrentGen());
    OtherIsland.EmptyIsland();
}


Generation& Island::GetCurrentGen() {
    return CurrentGen;
}

void Island::EmptyIsland() {
    CurrentGen.~Generation();
}

void Island::DevelopDuring(unsigned int NbGenerations) {
    for(int GenNum = 0; GenNum < NbGenerations; GenNum++) {
        CurrentGen = CurrentGen.Reproduce().Select(MaxVolume, NbBagsPerGen);
        History.push_back(CurrentGen.GetGenerationStats());
    }
    
}


void Island::PrintIslandHistory(string FileName) {
    ofstream ResultFile;
    ResultFile.open(FileName);
    
    ResultFile << "Index of Gen, Max Value of Gen, Average Value of Gen, Max nb of items / bag, Avg nb of items / bag\n";
    
    GenerationStats CurrentGenStats;
    for(int GenIndex = 0; GenIndex < History.size(); GenIndex++) {
        
        CurrentGenStats = History[GenIndex];
        ResultFile << GenIndex << "," << CurrentGenStats.MaxValue << "," << CurrentGenStats.AverageValue << "," << CurrentGenStats.MaxNbBags << "," << CurrentGenStats.AverageNbBags << "\n";

    }
    
    ResultFile.close();
}
