//
//  Generation.cpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#include "Generation.hpp"

Generation::Generation() : Population {} {
    
}

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

GenerationStats Generation::GetGenerationStats() {
    size_type SumValue = 0;
    size_type MaxValue = 0;
    size_type SumSquaresValue = 0;
    
    float SumNb = 0;
    unsigned long MaxNb = 0;
    float SumSquaresNb = 0;
    
    Mutation MaxMutationType = { };
    Mutation AvgMutationType = { };
    
    Mutation BagMutationType;
    for(auto BagIt = Population.begin(); BagIt<Population.end(); BagIt++) {
        if(MaxValue < BagIt->GetTotalValue()) MaxValue = BagIt->GetTotalValue();
        SumValue += BagIt->GetTotalValue();
        SumSquaresValue += pow(BagIt->GetTotalValue(), 2);
        
        if(MaxNb < BagIt->GetNumItems()) MaxNb = BagIt->GetNumItems();
        SumNb += BagIt->GetNumItems();
        SumSquaresNb += pow(BagIt->GetNumItems(), 2);
        
        BagMutationType = BagIt->GetMutationType();
        if(MaxMutationType.AdditionProbability < BagMutationType.AdditionProbability) {
            MaxMutationType.AdditionProbability = BagMutationType.AdditionProbability;
        }
        if(MaxMutationType.SubstractionProbability < BagMutationType.SubstractionProbability) {
            MaxMutationType.SubstractionProbability = BagMutationType.SubstractionProbability;
        }
        if(MaxMutationType.SubstitutionProbability < BagMutationType.SubstitutionProbability) {
            MaxMutationType.SubstitutionProbability = BagMutationType.SubstitutionProbability;
        }
        AvgMutationType.AdditionProbability += BagMutationType.AdditionProbability;
        AvgMutationType.SubstractionProbability += BagMutationType.SubstractionProbability;
        AvgMutationType.SubstitutionProbability += BagMutationType.SubstitutionProbability;
    }
    
    float AvgValue = SumValue/Population.size();
    float AvgNb = SumNb/Population.size();
    
    AvgMutationType.AdditionProbability /= (float)Population.size();
    AvgMutationType.SubstractionProbability /= (float)Population.size();
    AvgMutationType.SubstitutionProbability /= (float)Population.size();
    
    return GenerationStats(MaxValue, AvgValue, SumSquaresValue/Population.size() - pow(AvgValue,2), (unsigned int)MaxNb, AvgNb, SumNb/Population.size() - pow(AvgNb,2), MaxMutationType, AvgMutationType);
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
//    if(BestBags.GetPopulation().size() == 0) {
//        throw "Empty new gen";
//    }
    
    return BestBags;
}

Generation Generation::Reproduce() {
    return Reproduce(0, (int)Population.size()-1);
}

Generation Generation::Reproduce(int FirstIndex, int SecondIndex) {
    Generation NewGen {};
    
    if(FirstIndex >= Population.size() || SecondIndex >= Population.size()
       || FirstIndex > SecondIndex || FirstIndex < 0) {
        return NewGen;
        //throw "IndexOutOfRange";
    }
    int Bag1Index = 0;
    int Bag2Index = 0;
    
    Bag ChildBag {};
    for(auto Bag1It = Population.begin(); Bag1It < Population.end(); Bag1It++) {
        for(auto Bag2It = Population.begin(); Bag2It < Population.end(); Bag2It++) {
            if(Population.size() == 0) {
                throw "Empty pop";
            }
            if(Bag1It->GetNumItems() == 0 || Bag2It->GetNumItems() == 0) {
                throw "Empty bag";
            }
            ChildBag = Bag1It->Reproduce(*Bag2It);
            NewGen.AddBag(ChildBag);
            Bag2Index++;
        }
        Bag1Index++;
    }
    //NewGen.SetMutationType(MutationType); REMOVE
    return NewGen;
}


void Generation::Absorb(Generation& OtherGen){
    Population.insert(Population.end(), std::make_move_iterator(OtherGen.GetPopulation().begin()), std::make_move_iterator(OtherGen.GetPopulation().end()));
}


Generation Generation::InterGenerationReproduceMix(Generation& OtherGen) {
    
    
    //First half of each Gen reproduces with itself
    Generation NewGen = Reproduce(0, (int)Population.size() / 2);
    
    for(int i=0; i<NewGen.GetPopulation().size(); i++) {
        if(NewGen.GetPopulation()[i].GetNumItems() == 0) {
            throw "Here";
        }
    }
    
    Generation SecondGenHalfRep = OtherGen.Reproduce(0, (int)OtherGen.GetPopulation().size() / 2);
    NewGen.Absorb(SecondGenHalfRep);
    
    for(int i=0; i<NewGen.GetPopulation().size(); i++) {
        if(NewGen.GetPopulation()[i].GetNumItems() == 0) {
            throw "Here";
        }
    }
    
    //Second half reproduced with second half of other
    Generation SecondHalfInterReproduced = InterGenerationReproduce(OtherGen, (int)OtherGen.GetPopulation().size() / 2, (int)min(OtherGen.GetPopulation().size(), Population.size())-1);
    
    //We combine the two
    NewGen.Absorb(SecondHalfInterReproduced);
    
    for(int i=0; i<NewGen.GetPopulation().size(); i++) {
        if(NewGen.GetPopulation()[i].GetNumItems() == 0) {
            throw "Here";
        }
    }
    
//    Mutation NewMutationType = {
//        (MutationType.AdditionProbability + OtherGen.MutationType.AdditionProbability) / 2,
//        (MutationType.SubstractionProbability + OtherGen.MutationType.SubstractionProbability) / 2,
//        (MutationType.SubstitutionProbability + OtherGen.MutationType.SubstitutionProbability) / 2
//    }; REMOVE
     //NewGen.SetMutationType(NewMutationType); REMOVE
    
    return NewGen;
}


Generation Generation::InterGenerationReproduce(Generation& OtherGen, int FirstIndex, int SecondIndex) {
    
    if(FirstIndex >= Population.size() || SecondIndex >= Population.size()
       || FirstIndex >= OtherGen.GetPopulation().size() || SecondIndex >= OtherGen.GetPopulation().size() || FirstIndex > SecondIndex || FirstIndex < 0) {
        throw "IndexOutOfRange";
    }
    
    Generation NewGen {};
    Bag ChildBag {};
    for(auto Bag1It = Population.begin() + FirstIndex; Bag1It < Population.begin() + SecondIndex; Bag1It++) {
        for(auto Bag2It = OtherGen.GetPopulation().begin() + FirstIndex; Bag2It < OtherGen.GetPopulation().begin() + SecondIndex; Bag2It++) {
            ChildBag = Bag1It->Reproduce(*Bag2It);
            NewGen.AddBag(ChildBag);
        }
    }
    //NewGen.SetMutationType(MutationType);
    return NewGen;
}


vector<Bag>& Generation::GetPopulation() {
    return Population;
}
//
//void Generation::SetMutationType(Mutation MutationType_in) {
//    MutationType = MutationType_in;
//} REMOVE




template<int N, class ... Types>
void GenerationStats::PrintTitles(ostream& OutFile) {
    
    PrintTitle<type_at<N, Types...>::type>(OutFile);
    PrintTitle<N-1, Types...>(OutFile);
}

template<>
void GenerationStats::PrintTitles<-1>(ostream& OutFile) {
    //End of compile time loop, do nothing
}

template<class ... Types>
void GenerationStats::PrintTitle(ostream& OutFile) {
    const int NumberOfTypes = sizeof...(Types);
    
    return PrintTitle<type_at<NumberOfTypes, Types...>::type, Types...>(OutFile);
}



//template<int N, class ... Types>
//void GenerationStats::PrintContent(ostream& OutFile) {
//
//    PrintContent<type_at<N, Types...>::type>(OutFile);
//    PrintContent<N-1, Types...>(OutFile);
//}
//
//template<>
//void GenerationStats::PrintContent<-1>(ostream& OutFile) {
//    //End of compile time loop, do nothing
//}
//
//template<class ... Types>
//void GenerationStats::PrintContent(ostream& OutFile) {
//    const int NumberOfTypes = sizeof...(Types);
//
//    return PrintContent<type_at<NumberOfTypes, Types...>::type>(OutFile);
//}
//



//
//
//template<>
//struct GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::MaxValue_type
//>(ostream& OutFile) {
//    OutFile << "Maximum value of generation, ";
//}
//
//
////TRANSFORM IT IN CLASSES like traits ? (see class notes)
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::MaxValue_type
//>(ostream& OutFile) {
//    OutFile << "Maximum value of generation, ";
//}
//
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::AverageValue_type
//>(ostream& OutFile) {
//    OutFile << "Average value of generation, ";
//}
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::StdVarValue_type
//>(ostream& OutFile) {
//    OutFile << "Standard deviation of generation, ";
//}
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::MaxNbItemsPerBag_type
//>(ostream& OutFile) {
//    OutFile << "Maximum number of items per bag, ";
//}
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::AverageNbItemsPerBag_type
//>(ostream& OutFile) {
//    OutFile << "Average number of items per bag, ";
//}
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::StdVarNbItemsPerBag_type
//>(ostream& OutFile) {
//    OutFile << "Standard deviation nb items, ";
//}
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::MaxMutationType_type
//>(ostream& OutFile) {
//    OutFile << "Max Add value of Mutation, ";
//    OutFile << "Max Substract value of Mutation, ";
//    OutFile << "Max Substit value of Mutation, ";
//}
//
//template<>
//void GenerationStats::PrintTitle<
//GenerationStats::GenerationStatsTraits::AverageMutationType_type
//>(ostream& OutFile) {
//    OutFile << "Average Add value of Mutation, ";
//    OutFile << "Average Substract value of Mutation, ";
//    OutFile << "Average Substit value of Mutation, ";
//}
