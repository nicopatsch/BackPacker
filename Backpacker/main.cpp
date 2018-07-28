#include "Item.hpp"
#include "Pool.hpp"
#include "Generation.hpp"
#include "Bag.hpp"


int main(int argc, const char * argv[]) {
    
    Pool ThePoolSingleton = Pool::GetInstance();
    ThePoolSingleton.PrintContent();
    
    const unsigned int MaxVolume = 2000;
    const unsigned int NbBagsPerGen = 20;
    
    Mutation ModerateMutation = { 0.2, 0.2, 0.2 };
    Mutation NoMutation = { 0., 0., 0. };
    Mutation HighMutation = { 0.5, 0.5, 0.5 };
    
    Generation CurrentGen = ThePoolSingleton.GenerateRandomBags(10);
    cout << "Generation 0" << endl;
    CurrentGen.PrintGenerationCompact();
    
    for(int GenNum = 0; GenNum < 10; GenNum++) {
        CurrentGen = CurrentGen.Reproduce(NoMutation).Select(MaxVolume, NbBagsPerGen);
        cout << "Generation " << GenNum << endl;
        CurrentGen.PrintGenerationCompact();
    }
    
    
    
    return 0;
}
