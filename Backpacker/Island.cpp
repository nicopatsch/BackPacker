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


Island::Island() : Island(0, 0){
    
}


Island::Island(unsigned int MaxVolume_in, unsigned NbBagsPerGen_in) : MaxVolume { MaxVolume_in }, NbBagsPerGen { NbBagsPerGen_in } {
    CurrentGen = Pool::GetInstance().GenerateRandomBags(NbBagsPerGen_in);
    Pool::GetInstance().PrintContent();
    //CurrentGen.SetMutationType(MutationType); REMOVE
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
        ResultFile << GenIndex << "," << CurrentGenStats.MaxValue << "," << CurrentGenStats.AverageValue << "," << CurrentGenStats.MaxNbItemsPerBag << "," << CurrentGenStats.AverageNbItemsPerBag << "\n";

    }
    
    ResultFile.close();
}



void Island::PrintAllIslandsHistory(string FileName, vector<shared_ptr<Island>> Islands) {
    ofstream ResultFile;
    ResultFile.open(FileName);
    
    //Print all titles
    ResultFile << "Index of Gen, ";
    for(int i = 0; i < Islands.size(); i++) {
        ResultFile << "I#" << i+1 << ": Max Value of Gen, ";
        ResultFile << "I#" << i+1 << ": Average Value, ";
        ResultFile << "I#" << i+1 << ": Standard Deviation of Value, ";
        
        ResultFile << "I#" << i+1 << ": Max nb of items / bag, ";
        ResultFile << "I#" << i+1 << ": Avg nb of items,";
        ResultFile << "I#" << i+1 << ": Standard Deviation nb of items, ";
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
                
                ResultFile
                << CurrentGenStats.MaxValue << ","
                << CurrentGenStats.AverageValue << ","
                << CurrentGenStats.StdVarValue << ","
                
                << CurrentGenStats.MaxNbItemsPerBag << ","
                << CurrentGenStats.AverageNbItemsPerBag << ","
                << CurrentGenStats.StdVarNbItemsPerBag << ",";
            }
            else {
                ResultFile << " , , , , , , ";
            }
            
        }
        ResultFile << "\n";
        GenIndex++;
    }
}

void Island::PrintAllIslandsHistoryValue(string FileName, vector<shared_ptr<Island>> Islands) {
    ofstream ResultFile;
    ResultFile.open(FileName);
    
    //Print all titles
    ResultFile << "Index of Gen, ";
    for(int i = 0; i < Islands.size(); i++) {
        ResultFile << "I#" << i+1 << ": Max Value of Gen, ";
        ResultFile << "I#" << i+1 << ": Average Value, ";
        ResultFile << "I#" << i+1 << ": Standard Deviation of Value, ";
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
                
                ResultFile
                << CurrentGenStats.MaxValue << ","
                << CurrentGenStats.AverageValue << ","
                << CurrentGenStats.StdVarValue << ",";
            }
            else {
                ResultFile << " , , , ";
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


void Island::PrintAllIslandsHistoryMutations(string FileName, vector<shared_ptr<Island>> Islands) {
    ofstream ResultFile;
    ResultFile.open(FileName);
    
    //Print all titles
    ResultFile << "Index of Gen, ";
    for(int i = 0; i < Islands.size(); i++) {
        ResultFile << "I#" << i+1 << ": Average AdditionProb of Gen, Average SubstractionProb of Gen, Average SubstitutionProb of Gen, ";
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
                
                ResultFile
                << CurrentGenStats.AverageMutationType.AdditionProbability << ","
                << CurrentGenStats.AverageMutationType.SubstractionProbability << ","
                << CurrentGenStats.AverageMutationType.SubstitutionProbability << ",";
            }
            else {
                ResultFile << " , , , ";
            }
            
        }
        ResultFile << "\n";
        GenIndex++;
    }
}


//template <class ... Args>
//void Island::PrintAllIslandsHistory(string FileName, vector<shared_ptr<Island>> Islands) {
//    
//    ofstream ResultFile;
//    ResultFile.open(FileName);
//    
//    //Print all the necesary titles
//    ResultFile << "Index of Gen, ";
//    GenerationStats::PrintTitle<Args...>(ResultFile);
//    ResultFile << "\n";
//    
//    int GenIndex = 0;
//    int NbIslandsStillRuning = (int)Islands.size();
//    GenerationStats CurrentGenStats;
//    
//    while(NbIslandsStillRuning > 0) {
//        ResultFile << GenIndex << ",";
//        NbIslandsStillRuning = 0;
//        
//        for(auto IslandIt = Islands.begin(); IslandIt < Islands.end(); IslandIt++) {
//            if((*IslandIt)->History.size() > GenIndex) {
//                CurrentGenStats = (*IslandIt)->History[GenIndex];
//                NbIslandsStillRuning++;
//                
//                CurrentGenStats.PrintContent<Args...>(ResultFile);
//            }
//            
//        }
//        ResultFile << "\n";
//        GenIndex++;
//    }
//    
//    
//    
//    
//    cout << "Impression de " << sizeof...(Args) << " parametres: ";
//    print_(std::forward<Args>(args)...);
//    }
//}
//
//
//
//


//char* serialiser_brut(
//
//char* Island::serialiser_brut(char *dest) {
//    auto sznom = min<int>(nom.size(), SZ_NOM);
//    copy(begin(nom), begin(nom) + sznom, dest);
//    //...??
//    dest += SZ_NOM;
//    dest = ::serialiser_brut(pos.x, dest);
//    dest = ::serialiser_brut(pos.y, dest);
//    dest = ::serialiser_brut(pos.z, dest);
//    dest = ::serialiser_brut(puanteur, dest);
//    dest = ::serialiser_brut(force, dest);
//    dest = ::serialiser_brut(static_cast<char>(force), dest);
//    return dest;
//}
//         
//static const char* Island::deserialiser_brut(const char *src, Island &dest) {
//    char nom_[SZ_NOM +1] {};
//    copy(src, src + SZ_NOM, begin(nom_));
//    string nom = nom_;
//    int x;
//    copy(src, src + sizeof x, reinterpret_cast<char*>(&x));
//}



void Island::AddGenerationStats(GenerationStats GS) {
    History.push_back(GS);
}

GenerationStats Island::GetStatsOfGeneration(int i) const {
    return History[i];
}

void Island::SaveIslandToFile(string FileName) {
    
    ofstream BackupFile;
    BackupFile.open(FileName);
    
    BackupFile << *this;
    BackupFile.close();
}


void Island::ReadIslandFromFile(string FileName) {
    ifstream SourceFile;
    SourceFile.open(FileName);
    
    SourceFile >> *this;
    SourceFile.close();
    
}
