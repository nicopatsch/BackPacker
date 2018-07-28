
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
using size_type = float;
const unsigned int MAX_NB_OJECTS_BAG = 20; //The maximum number of objects a bag can contain
const unsigned int MAX_OBJECT_VALUE = 100;
const unsigned int MAX_OBJECT_VOLUME = 100;
const unsigned int NB_OBJECTS_IN_POOL = 10;

size_type RandomVal(const int Max) {
    return drand48()*Max;
}

class Object {
    unsigned int id;
    size_type Volume;
    size_type Value;
    
public:
    Object(unsigned int id_in, size_type Volume_in, size_type Value_in) : id { id_in }, Volume { Volume_in }, Value { Value_in } {};
    
    
    size_type GetVolume() const { return Volume; }
    size_type GetValue() const { return Value; }
    void PrintObject() const {
        cout << "Object number " << id << " -> Volume : " << Volume << " ; Value " << Value << "\n";
    }
    
};


class Bag {
    vector<Object*> Content;
    size_type TotalVolume;
    size_type TotalValue;
    
public:
    size_type GetTotalVolume() const { return TotalVolume; }
    size_type GetTotalValue() const { return TotalValue; }
    unsigned long GetNumObjects() const { return Content.size(); }
    Object* GetObjectByIndex(unsigned int Index) { return Content[Index]; }
    
    Bag() : TotalVolume {}, TotalValue{}, Content{} {};
    void PrintContent() const {
        cout << "Content of the Bag nb " << this << "\n";
        for (auto it = Content.begin(); it < Content.end(); it++) {
            (*it)->PrintObject();
        }
        cout << "\nTotal Value : " << GetTotalValue() << "\nTotal Volume : " << GetTotalVolume() << "\n";
    }
    
    void PrintPerformence() const {
        cout << "Performence of the Bag nb " << this;
        cout << " : " << GetNumObjects() << " objects for a total value of " << GetTotalValue() << ", total volume of " << GetTotalVolume() << "\n";
    }
    void PrintPerformenceShort() const {
        cout << "Bag nb " << this;
        cout << " : " << GetNumObjects() << " objects, TValue : " << GetTotalValue() << ", TVolume : " << GetTotalVolume() << "\n";
    }
    
    void AddObject(Object* pObj) {
        if(Content.size() < MAX_NB_OJECTS_BAG) {
            Content.push_back(pObj);
            TotalVolume += pObj->GetVolume();
            TotalValue += pObj->GetValue();
        }
    }
    
    bool IsViable(int MaxVolume) { return TotalVolume <= MaxVolume; }
    
    Bag Reproduce(Bag& Partner) {
        Bag ChildBag;
        int CurrObject = 0;
        while(this->GetNumObjects() > CurrObject || Partner.GetNumObjects() > CurrObject) {
            if(CurrObject % 2 == 0 && this->GetNumObjects() > CurrObject) {
                ChildBag.AddObject(this->GetObjectByIndex(CurrObject));
            }
            else if(CurrObject % 2 == 1 && Partner.GetNumObjects() > CurrObject) {
                ChildBag.AddObject(Partner.GetObjectByIndex(CurrObject));
            }
            CurrObject++;
        }
        return ChildBag;
    }
    
};



class Generation {
    vector<Bag> Population;
    
public:
    Generation() : Population {} {};
    void PrintGenerationCompact() {
        int SumValue = 0;
        int MaxValue = 0;
        
        for(auto BagIt = Population.begin(); BagIt<Population.end(); BagIt++) {
            BagIt->PrintPerformenceShort();
            if(MaxValue < BagIt->GetTotalValue()) MaxValue = BagIt->GetTotalValue();
            SumValue += BagIt->GetTotalValue();
        }
        cout << "\nMAX VALUE -> " << MaxValue << "\nAVERAGE VALUE -> " << SumValue/Population.size() << "\n\n";
    }
    
    void PrintGenerationFull() {
        for(auto BagIt = Population.begin(); BagIt<Population.end(); BagIt++) {
            BagIt->PrintContent();
            cout << " ----------------- \n";
        }
    }
    
    void AddBag(Bag NewBag) {
        Population.push_back(NewBag);
    }
    
    unsigned long GetNbBags() const { return Population.size(); }
    
    Generation Select(const unsigned int MaxVolume, const unsigned int MaxNbBags) {
        
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
        
        return BestBags;
    }
    
    Generation Reproduce() {
        Generation NewGen {};
        Bag ChildBag {};
        for(auto Bag1It = Population.begin(); Bag1It < Population.end(); Bag1It++) {
            for(auto Bag2It = Population.begin(); Bag2It < Population.end(); Bag2It++) {
                ChildBag = Bag1It->Reproduce(*Bag2It);
                NewGen.AddBag(ChildBag);
            }
        }
        return NewGen;
    }

};

class Pool {
    vector<Object> Content;
    const unsigned int NumObjects;
    
public:
    Pool(unsigned int NumObjects_in) : NumObjects { NumObjects_in } {
        Content.reserve(NumObjects_in);
    }
    Object* GetObjectByIndex(unsigned int Index) { return &Content[Index]; }
    
    void FillPool() {
        cout << "Content of the Pool nb " << this << "\n";
        for(int i = 0 ; i < NumObjects; i++) {
            Content.push_back(Object(i, RandomVal(MAX_OBJECT_VALUE), RandomVal(MAX_OBJECT_VOLUME)));
        }
        cout << "\n";
    }
    Generation GenerateRandomBags(unsigned int N) {
        Generation G {};
        for(int BagIndex = 0; BagIndex < N; BagIndex++) {
            Bag Individual {};
            unsigned int NumberOfObjects = rand() % MAX_NB_OJECTS_BAG;
            for(int ObjectIndex = 0; ObjectIndex < NumberOfObjects; ObjectIndex++) {
                Individual.AddObject(GetObjectByIndex(rand() % NumObjects));
            }
            G.AddBag(Individual);
        }
        return G;
    }
    
    void PrintContent() const {
        for (auto it = Content.begin(); it < Content.end(); it++) {
            it->PrintObject();
        }
    }
    
};



int main(int argc, const char * argv[]) {
    
    Pool MyPool { NB_OBJECTS_IN_POOL };
    MyPool.FillPool();
    MyPool.PrintContent();
    
    
    const unsigned int MaxVolume = 2000;
    const unsigned int NbBagsPerGen = 20;
    
    
    
    Generation CurrentGen = MyPool.GenerateRandomBags(10);
    cout << "Generation 0" << endl;
    CurrentGen.PrintGenerationCompact();
    
    for(int GenNum = 0; GenNum < 10; GenNum++) {
        CurrentGen = CurrentGen.Reproduce().Select(MaxVolume, NbBagsPerGen);
        cout << "Generation " << GenNum << endl;
        CurrentGen.PrintGenerationCompact();
    }
    
    
    return 0;
}
