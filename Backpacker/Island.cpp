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

void Island::Absorb(Island& OtherIsland) {
    if(CurrentGen.GetPopulation().size() <= 0) {
        //Invasion of a dead Island
        CurrentGen = OtherIsland.GetCurrentGen();
    }
    else if(OtherIsland.GetCurrentGen().GetPopulation().size() <= 0) {
        //Nothing happens because the other Island is dead
    }
    else {
        CurrentGen = CurrentGen.InterGenerationReproduceMix(OtherIsland.GetCurrentGen());
        CurrentGen = CurrentGen.Select(MaxVolume, NbBagsPerGen);
    }
    
    //Previous implementation:
    //CurrentGen.Absorb(OtherIsland.GetCurrentGen());
}


Generation& Island::GetCurrentGen() {
    return CurrentGen;
}


void Island::DevelopDuring(unsigned int NbGenerations) {
    for(int GenNum = 0; GenNum < NbGenerations; GenNum++) {
        CurrentGen = CurrentGen.Reproduce().Select(MaxVolume, NbBagsPerGen);
        if(CurrentGen.GetPopulation().size() <= 0) {
            cout << "Extinct Island " << this << "On generation #" << History.size() << "\n";
            break;
        }
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



void Island::PrintAllIslandsHistory(string FileName, vector<Island*> Islands) {
    ofstream ResultFile;
    ResultFile.open(FileName);
    
    //Print all titles
    ResultFile << "Index of Gen, ";
    for(int i = 0; i < Islands.size(); i++) {
        ResultFile << "I#" << i+1 << ": Max Value of Gen, ";
        ResultFile << "I#" << i+1 << ": Average Value of Gen, ";
        ResultFile << "I#" << i+1 << ": Max nb of items / bag, ";
        ResultFile << "I#" << i+1 << ": Avg nb of items / bag,";
    }
    ResultFile << "\n";
    
    int GenIndex = 0;
    int NbIslandsStillRuning = (int)Islands.size();
    GenerationStats CurrentGenStats;
    
    while(NbIslandsStillRuning > 0) {
        ResultFile << GenIndex << ",";
        NbIslandsStillRuning = 0;
        
        for(auto IslandIt = Islands.begin(); IslandIt < Islands.end(); IslandIt++) {
            if((*IslandIt)->History.size() > GenIndex) {
                CurrentGenStats = (*IslandIt)->History[GenIndex];
                NbIslandsStillRuning++;
                
                ResultFile << CurrentGenStats.MaxValue << "," << CurrentGenStats.AverageValue << "," << CurrentGenStats.MaxNbBags << "," << CurrentGenStats.AverageNbBags << ",";
            }
            else {
                ResultFile << " , , , ,";
            }
            
        }
        ResultFile << "\n";
        GenIndex++;
    }
}



void Island::PrintAllIslandsHistoryShort(string FileName, vector<shared_ptr<Island>> Islands) {
    ofstream ResultFile;
    ResultFile.open(FileName);
    
    //Print all titles
    ResultFile << "Index of Gen, ";
    for(int i = 0; i < Islands.size(); i++) {
        ResultFile << "I#" << i+1 << ": Average Value of Gen, ";
    }
    ResultFile << "\n";
    
    int GenIndex = 0;
    int NbIslandsStillRuning = (int)Islands.size();
    GenerationStats CurrentGenStats;
    
    while(NbIslandsStillRuning > 0) {
        ResultFile << GenIndex << ",";
        NbIslandsStillRuning = 0;
        
        for(auto IslandIt = Islands.begin(); IslandIt < Islands.end(); IslandIt++) {
            if((*IslandIt)->History.size() > GenIndex) {
                CurrentGenStats = (*IslandIt)->History[GenIndex];
                NbIslandsStillRuning++;
                
                ResultFile << CurrentGenStats.AverageValue << ",";
            }
            else {
                ResultFile << " ,";
            }
            
        }
        ResultFile << "\n";
        GenIndex++;
    }
}
