#include "Item.hpp"
#include "Pool.hpp"
#include "Generation.hpp"
#include "Bag.hpp"
#include "Island.hpp"

#include <fstream>
#include <string>
#include <iostream>


void FirstExperiment() {
    Pool ThePoolSingleton = Pool::GetInstance();
    ThePoolSingleton.PrintContent();
    
    const unsigned int MaxVolume = 500;
    const unsigned int NbBagsPerGen = 20;
    
    Mutation ModerateMutation = { 0.1, 0.1, 0.1 };
    Mutation NoMutation = { 0., 0., 0. };
    Mutation HighMutation = { 0.5, 0.5, 0.5 };
    
    Generation CurrentGen = ThePoolSingleton.GenerateRandomBags(10);
    cout << "Generation 0" << endl;
    CurrentGen.PrintGenerationCompact();
    
    GenerationStats ResultStats;
    ofstream ResultFile;
    ResultFile.open("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/results.txt");
    
    ResultFile << "Index of Gen, Max Value of Gen, Average Value of Gen, Max nb of items / bag, Avg nb of items / bag\n";
    for(int GenNum = 0; GenNum < 500; GenNum++) {
        CurrentGen = CurrentGen.Reproduce().Select(MaxVolume, NbBagsPerGen);
        cout << "Generation " << GenNum << endl;
        CurrentGen.PrintGenerationCompact();
        ResultStats = CurrentGen.GetGenerationStats();
        ResultFile << GenNum << "," << ResultStats.MaxValue << "," << ResultStats.AverageValue << ",";
        
        ResultFile << ResultStats.MaxNbBags << "," << ResultStats.AverageNbBags << "\n";
    }
    
    ResultFile.close();
    
}

void SecondExperiment() {
    Pool ThePoolSingleton = Pool::GetInstance();
    
    const unsigned int MaxVolume = 500;
    const unsigned int NbBagsPerGen = 20;
    
    
    Mutation ModerateMutation = { 0.1, 0.1, 0.1 };
    Mutation NoMutation = { 0., 0., 0. };
    Mutation HighMutation = { 0.5, 0.5, 0.5 };
    
    Island Island1 = Island(MaxVolume, NbBagsPerGen, ModerateMutation);
    Island1.DevelopDuring(1000);
    
    Island1.PrintIslandHistory("/Users/nicopatsch/OneDrive - USherbrooke/@PROGRAMMING/Backpacker/results.txt");
    
}

int main(int argc, const char * argv[]) {
    
    SecondExperiment();
    
    return 0;
    
}
