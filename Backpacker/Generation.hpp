//
//  Generation.hpp
//  Backpacker
//
//  Created by Nicolas Patschkowski on 28/07/2018.
//  Copyright © 2018 Nicolas Patschkowski. All rights reserved.
//

#ifndef Generation_hpp
#define Generation_hpp

#include <stdio.h>
#include <iostream>
#include "Item.hpp"
#include "Bag.hpp"


class str_const { // constexpr string
private:
    const char* const p_;
    const std::size_t sz_;
public:
    template<std::size_t N>
    constexpr str_const(const char(&a)[N]) : // ctor
    p_(a), sz_(N-1) {}
    constexpr char operator[](std::size_t n) { // []
        return n < sz_ ? p_[n] :
        throw std::out_of_range("");
    }
    constexpr std::size_t size() { return sz_; } // size()
};

struct GenerationStats { //Stats of one generation for history recording
    
    static constexpr str_const MaxValue_type = "MaxValue";
    
    struct GenerationStatsTraits {
        class MaxValue_type;
        class AverageValue_type;
        class StdVarValue_type;
        
        class MaxNbItemsPerBag_type;
        class AverageNbItemsPerBag_type;
        class StdVarNbItemsPerBag_type;
        
        class MaxMutationType_type;
        class AverageMutationType_type;

    };
    
    
    size_type MaxValue;
    size_type AverageValue;
    size_type StdVarValue;
    
    unsigned int MaxNbItemsPerBag;
    float AverageNbItemsPerBag;
    float StdVarNbItemsPerBag;
    
    Mutation MaxMutationType;
    Mutation AverageMutationType;
    
    GenerationStats() {};
    GenerationStats(size_type MaxValue_in,
                    size_type AverageValue_in,
                    size_type StdVarValue_in,
                    unsigned int MaxNbItemsPerBag_in,
                    float AverageNbItemsPerBag_in,
                    float StdVarNbItemsPerBag_in,
                    Mutation MaxMutationType_in,
                    Mutation AverageMutationType_in):
    MaxValue { MaxValue_in },
    AverageValue { AverageValue_in },
    StdVarValue { StdVarValue_in },
    MaxNbItemsPerBag { MaxNbItemsPerBag_in },
    AverageNbItemsPerBag { AverageNbItemsPerBag_in },
    StdVarNbItemsPerBag { StdVarNbItemsPerBag_in },
    MaxMutationType { MaxMutationType_in },
    AverageMutationType { AverageMutationType_in } {}
    
    
    friend std::ostream& operator<<(std::ostream& os, const GenerationStats& TheGS)
    {
        // write out individual members of s with an end of line between each one
        os << TheGS.MaxValue << '\n';
        os << TheGS.AverageValue << '\n';
        os << TheGS.StdVarValue << '\n';
        
        os << TheGS.MaxNbItemsPerBag << '\n';
        os << TheGS.AverageNbItemsPerBag << '\n';
        os << TheGS.StdVarNbItemsPerBag << '\n';
        
        os << TheGS.MaxMutationType << '\n';
        os << TheGS.AverageMutationType;
        
        return os;
    }
    
    // Extraction operator
    friend std::istream& operator>>(std::istream& is, GenerationStats& TheGS)
    {
        // read in individual members of s
        is >> TheGS.MaxValue >> TheGS.AverageValue >> TheGS.StdVarValue >> TheGS.MaxNbItemsPerBag >> TheGS.AverageNbItemsPerBag >> TheGS.StdVarNbItemsPerBag >> TheGS.MaxMutationType >> TheGS.AverageMutationType;
        return is;
    }
    
    
    
    
    template<class VarType>
    static void PrintTitle(ostream& OutFile);
    
    template<int N, class ... Types>
    static void PrintTitles(ostream& OutFile);
    
    template<class ... Types>
    static void PrintTitle(ostream& OutFile);
    
    
    
    
//    template<class VarType>
//    void PrintContent(ostream& OutFile);
//
//    template<int N, class ... Types>
//    void PrintContent(ostream& OutFile);
//
//    template<class ... Types>
//    void PrintContent(ostream& OutFile);
};



class Generation {
    vector<Bag> Population;
    //Mutation MutationType; REMOVE
    
public:
    Generation();
    //Generation(Mutation MutationType); REMOVE
    void PrintGenerationCompact();
    GenerationStats GetGenerationStats();
    void PrintGenerationFull();
    
    void AddBag(Bag NewBag);
    
    unsigned long GetNbBags() const;
    
    Generation Select(const unsigned int MaxVolume, const unsigned int MaxNbBags);
    Generation Reproduce();
    Generation Reproduce(int FirstIndex, int SecondIndex);
    //void SetMutationType(Mutation MutationType_in); REMOVE
    
    vector<Bag>& GetPopulation();
    void Absorb(Generation& OtherGen);
    Generation InterGenerationReproduce(Generation& OtherGen, int FirstIndex, int SecondIndex);
    Generation InterGenerationReproduceMix(Generation& OtherGen);
        
    pair<unsigned int, unsigned int> GetNbItemsPerBag();
    
};


template <unsigned N, typename FirstType, typename ...RemainingTypes>
struct type_at {
    typedef typename type_at<N - 1, RemainingTypes...>::type type;
};

template <typename FirstType, typename ...RemainingTypes>
struct type_at<0, FirstType, RemainingTypes...> {
    typedef FirstType type;
};


#endif /* Generation_hpp */
