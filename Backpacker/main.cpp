#include "Item.hpp"
#include "Pool.hpp"
#include "Generation.hpp"
#include "Bag.hpp"
#include "Island.hpp"

#include <fstream>
#include <string>
#include <iostream>

const unsigned int MaxVolume = 500;
const unsigned int NbBagsPerGen = 100;

Mutation NoMutation = { 0., 0., 0. };
Mutation LowMutation = { 0.2, 0.2, 0.2 };
Mutation ModerateMutation = { 0.5, 0.5, 0.5 };
Mutation HighMutation = { 1, 1, 1 };

void FirstExperiment() {
    
    shared_ptr<Island> Island1 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    Island1->DevelopDuring(5000);
    
    Island::PrintAllIslandsHistoryMutations("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/FirstExperimentResultsMutations.txt", { Island1 });
    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/FirstExperimentResultsShort.txt", { Island1 });
    Island::PrintAllIslandsHistory("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/FirstExperimentResults.txt", { Island1 });
    
    
}

void SecondExperiment() {
    
    shared_ptr<Island> Island1 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island2 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island3 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island4 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island5 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island6 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island7 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island8 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island9 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island10 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island11 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island12 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island13 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island14 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island15 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    shared_ptr<Island> Island16 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    
    const int DevelopmentDuration = 200;
    
    Island1->DevelopDuring(DevelopmentDuration);
    Island2->DevelopDuring(DevelopmentDuration);
    Island3->DevelopDuring(DevelopmentDuration);
    Island4->DevelopDuring(DevelopmentDuration);
    Island5->DevelopDuring(DevelopmentDuration);
    Island6->DevelopDuring(DevelopmentDuration);
    Island7->DevelopDuring(DevelopmentDuration);
    Island8->DevelopDuring(DevelopmentDuration);
    Island9->DevelopDuring(DevelopmentDuration);
    Island10->DevelopDuring(DevelopmentDuration);
    Island11->DevelopDuring(DevelopmentDuration);
    Island12->DevelopDuring(DevelopmentDuration);
    Island13->DevelopDuring(DevelopmentDuration);
    Island14->DevelopDuring(DevelopmentDuration);
    Island15->DevelopDuring(DevelopmentDuration);
    Island16->DevelopDuring(DevelopmentDuration);
    
    Island1->Absorb(*Island5);
    Island2->Absorb(*Island6);
    Island3->Absorb(*Island7);
    Island4->Absorb(*Island8);
    Island5->Absorb(*Island5);
    Island6->Absorb(*Island6);
    Island7->Absorb(*Island7);
    Island8->Absorb(*Island8);
    
    
    Island1->DevelopDuring(DevelopmentDuration);
    Island2->DevelopDuring(DevelopmentDuration);
    Island3->DevelopDuring(DevelopmentDuration);
    Island4->DevelopDuring(DevelopmentDuration);
    Island5->DevelopDuring(DevelopmentDuration);
    Island6->DevelopDuring(DevelopmentDuration);
    Island7->DevelopDuring(DevelopmentDuration);
    Island8->DevelopDuring(DevelopmentDuration);
    
    Island1->Absorb(*Island5);
    Island2->Absorb(*Island6);
    Island3->Absorb(*Island7);
    Island4->Absorb(*Island8);
    
    Island1->DevelopDuring(DevelopmentDuration);
    Island2->DevelopDuring(DevelopmentDuration);
    Island3->DevelopDuring(DevelopmentDuration);
    Island4->DevelopDuring(DevelopmentDuration);

    Island1->Absorb(*Island3);
    Island2->Absorb(*Island4);

    Island1->DevelopDuring(DevelopmentDuration);
    Island2->DevelopDuring(DevelopmentDuration);

    Island1->Absorb(*Island2);
    Island1->DevelopDuring(3*DevelopmentDuration);

    Island::PrintAllIslandsHistoryValue("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/SecondExperimentResults.txt", { Island1, Island2, Island3, Island4, Island5, Island6, Island7, Island8 });
    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/SecondExperimentResultsShort.txt", { Island1, Island2, Island3, Island4, Island5, Island6, Island7, Island8 });
    Island::PrintAllIslandsHistoryMutations("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/SecondExperimentResultsMutations.txt", { Island1, Island2, Island3, Island4, Island5, Island6, Island7, Island8 });

    
}


void ThirdExperiment() {
    
    const int Duration = 500;
    int NbExperiments = 10;
    
    vector<shared_ptr<Island>> VariousIslands;
    for(int i = 0; i < NbExperiments; i++) {
        shared_ptr<Island> pIsland = make_shared<Island>(MaxVolume, NbBagsPerGen);
        VariousIslands.push_back(pIsland);
        VariousIslands[i]->DevelopDuring(Duration);
    }
    
    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/ThirdExperimentResultsShort.txt", VariousIslands);
    Island::PrintAllIslandsHistoryValue("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/ThirdExperimentResultsValue.txt", VariousIslands);
    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/ThirdExperimentResultsFull.txt", VariousIslands);
    
    
}

void FourthExperiment() {
    
    shared_ptr<Island> Island1 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    Island1->DevelopDuring(50000);
    
    shared_ptr<Island> Island2 = make_shared<Island>(MaxVolume, NbBagsPerGen);
    Island2->DevelopDuring(50000);
                           
    Island::PrintAllIslandsHistoryMutations("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/FirstExperimentResultsMutations.txt", { Island1, Island2 });
    Island::PrintAllIslandsHistoryShort("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/FirstExperimentResultsShort.txt", { Island1, Island2 });
    Island::PrintAllIslandsHistory("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/FirstExperimentResults.txt", { Island1, Island2 });
    
    Island1->SaveIslandToFile("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/SavedData/BigExperimentIsland1.txt");
    Island2->SaveIslandToFile("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/SavedData/BigExperimentIsland2.txt");
}


int main(int argc, const char * argv[]) {
    
    SecondExperiment();
    
    return 0;
    
}
