#include "Item.hpp"
#include "Pool.hpp"
#include "Generation.hpp"
#include "Bag.hpp"
#include "Island.hpp"

#include <fstream>
#include <string>
#include <iostream>

const unsigned int MaxVolume = 500;
const unsigned int NbBagsPerGen = 20;


Mutation ModerateMutation = { 0.1, 0.1, 0.1 };
Mutation NoMutation = { 0., 0., 0. };
Mutation HighMutation = { 0.5, 0.5, 0.5 };

void FirstExperiment() {
    
    Island Island1 = Island(MaxVolume, NbBagsPerGen, ModerateMutation);
    Island1.DevelopDuring(1000);
    Island1.PrintIslandHistory("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/results.txt");
    
    
}

void SecondExperiment() {
    
    
}

int main(int argc, const char * argv[]) {
    
    SecondExperiment();
    
    return 0;
    
}
