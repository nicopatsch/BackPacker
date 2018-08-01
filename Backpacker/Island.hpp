//
//  Island.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 29/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Island_hpp
#define Island_hpp

#include <stdio.h>
#include "Generation.hpp"
#include <string.h>


class Island {
    Generation CurrentGen;
    unsigned int MaxVolume;
    unsigned int NbBagsPerGen;
    vector<GenerationStats> History;
    
public:
    Island(unsigned int MaxVolume, unsigned NbBagsPerGen);
    Island();
    void Absorb(Island& OtherIsland);
    
    void PrintIslandHistory(string FileName);
    static void PrintAllIslandsHistory(string FileName, vector<shared_ptr<Island>> Islands);
    static void PrintAllIslandsHistoryValue(string FileName, vector<shared_ptr<Island>> Islands);
    static void PrintAllIslandsHistoryShort(string FileName, vector<shared_ptr<Island>> Islands);
    static void PrintAllIslandsHistoryMutations(string FileName, vector<shared_ptr<Island>> Islands);
    
    void SaveIslandToFile(string FileName);
    void ReadIslandFromFile(string FileName);
    
    void AddGenerationStats(GenerationStats GS);
    GenerationStats GetStatsOfGeneration(int i) const;
    
    template <class ... Args>
    static void PrintAllIslandsHistory(string FileName, vector<shared_ptr<Island>> Islands);
    
    void DevelopDuring(unsigned int NbGenerations);
    Generation& GetCurrentGen();
    
    // Insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Island& TheIsland)
    {
        // write out individual members of s with an end of line between each one
        os << TheIsland.MaxVolume << '\n';
        os << TheIsland.NbBagsPerGen << '\n';
        os << (int)TheIsland.History.size() << '\n';
        for(int i = 0; i < TheIsland.History.size(); i++) {
            os << TheIsland.GetStatsOfGeneration(i) << '\n';
        }
        return os;
    }
    
    // Extraction operator
    friend std::istream& operator>>(std::istream& is, Island& TheIsland)
    {
        // read in individual members of s
        int NbOfGenerations;
        GenerationStats GSTemp;
        
        is >> TheIsland.MaxVolume >> TheIsland.NbBagsPerGen >> NbOfGenerations;
        for(int i = 0; i < NbOfGenerations; i++) {
            is >> GSTemp;
            TheIsland.AddGenerationStats(GSTemp);
        }
        return is;
    }

};




#endif /* Island_hpp */
