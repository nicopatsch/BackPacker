#include "Item.hpp"
#include "Pool.hpp"
#include "Generation.hpp"
#include "Bag.hpp"
#include "Island.hpp"

#include <fstream>
#include <string>
#include <iostream>

const unsigned int MaxVolume = 500;
const unsigned int NbBagsPerGen = 40;

Mutation NoMutation = { 0., 0., 0. };
Mutation LowMutation = { 0.2, 0.2, 0.2 };
Mutation ModerateMutation = { 0.5, 0.5, 0.5 };
Mutation HighMutation = { 1, 1, 1 };

void FirstExperiment() {
    
    Island Island1 = Island(MaxVolume, NbBagsPerGen, ModerateMutation);
    Island1.DevelopDuring(1000);
    Island1.PrintIslandHistory("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/results.txt");
    
}

void SecondExperiment() {
    
//    Island Island1 = Island(MaxVolume, NbBagsPerGen, HighMutation);
//    Island Island2 = Island(MaxVolume, NbBagsPerGen, ModerateMutation);
//    Island Island3 = Island(MaxVolume, NbBagsPerGen, LowMutation);
//    Island Island4 = Island(MaxVolume, NbBagsPerGen, NoMutation);
//    
//    Island1.DevelopDuring(200);
//    Island2.DevelopDuring(200);
//    Island3.DevelopDuring(200);
//    Island4.DevelopDuring(200);
//
//    Island1.Absorb(Island3);
//    Island2.Absorb(Island4);
//
//    Island1.DevelopDuring(200);
//    Island2.DevelopDuring(200);
//
//    Island1.Absorb(Island2);
//    Island1.DevelopDuring(200);
//
//    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/SecondExperimentResults.txt", { &Island1, &Island2, &Island3, &Island4 });

    
}


void ThirdExperiment() {
    
    const int Duration = 500;
    int NbExperiments = 10;
    
    vector<Mutation> VariousMutations;
    for(int i = 0; i < NbExperiments; i++) {
        const float r = i/10.;
        VariousMutations.push_back({ r, r, r });
    }
    
    vector<shared_ptr<Island>> VariousIslands;
    for(int i = 0; i < NbExperiments; i++) {
        shared_ptr<Island> pIsland = make_shared<Island>(MaxVolume, NbBagsPerGen, VariousMutations[i]);
        VariousIslands.push_back(pIsland);
        VariousIslands[i]->DevelopDuring(Duration);
    }
    
    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/ThirdExperimentResults.txt", VariousIslands);
    
    
}



int main(int argc, const char * argv[]) {
    
    ThirdExperiment();
    
    return 0;
    
}
