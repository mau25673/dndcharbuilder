#ifndef CHARACTERCLASS_H
#define CHARACTERCLASS_H

#include <string>
#include <vector>
#include <tuple>
using namespace std;

class characterClass
{
protected:
    string name;
    vector<tuple<int, string, string>> features;
public:
    characterClass();
    characterClass(string name, vector<tuple<int, string, string>> features){
        this->name = name;
        this->features = features;
    }
    string getName() const {return this->name;}
    vector<tuple<int, string, string>> getFeatures() const;
    string getFeatureName(size_t index) const;
    int getFeatureLevel(size_t index) const;
    string getFeatureDescription(size_t index) const;

    void setName(string name);
};
//classes
class fighterClass : public characterClass{
    public:
        fighterClass() {}
        fighterClass(string name, vector<tuple<int, string, string>> features){
            this->name = name;
            this->features = features;
        }
};
class rogueClass : public characterClass{
    protected:
        pair<int,int> sneakAttack;
    public:
        rogueClass() {}
        rogueClass(string name, vector<tuple<int, string, string>> features){
            this->name = name;
            this->features = features;
            this->sneakAttack = pair(1, 6);
        }
        void SetSneakAttack(pair<int,int> sneakAttack);
        pair<int,int> GetSneakAttack() const;
};
class clericClass : public characterClass{
    protected:
        vector<tuple<int,string,string>> spellList;
        vector<pair<int,int>> spellSlots;
    public:
        clericClass() {}
        clericClass(string name, vector<tuple<int, string, string>> features){
            this->name = name;
            this->features = features;
        }
        void SetSpellList(vector<tuple<int,string,string>> spellList);
        void SetSpellSlots(vector<pair<int,int>> spellSlots);

        vector<tuple<int,string,string>> GetSpellList();
};
class wizardClass : public characterClass{
    protected:
        vector<tuple<int,string,string>> spellList;
        vector<pair<int,int>> spellSlots;
    public:
        wizardClass() {}
        wizardClass(string name, vector<tuple<int, string, string>> features){
            this->name = name;
            this->features = features;
        }
        void SetSpellList(vector<tuple<int,string,string>> spellList);
        void SetSpellSlots(vector<pair<int,int>> spellSlots);

        vector<tuple<int,string,string>> GetSpellList();
};


class subClass{
    protected:
        string name;
        vector<tuple<int, string, string>> subClassFeatures;
    public:
        subClass() {}

        string GetName() const;
        string getFeatureName(size_t index) const;
        int getFeatureLevel(size_t index) const;
        string getFeatureDescription(size_t index) const;
        vector<tuple<int, string, string>> getFeatures() const;
};
//fighter subclasses
class Champion : public subClass{
    public:
        Champion(){}
        Champion(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
class BattleMaster : public subClass{
    public:
        BattleMaster() {}
        BattleMaster(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
//rogue subclasses
class Assassin : public subClass{
    public:
        Assassin(){}
        Assassin(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
class Thief : public subClass{
    public:
        Thief(){}
        Thief(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
//wizard subclasses
class Abjuration : public subClass{
    public:
        Abjuration() {}
        Abjuration(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
class Transmutation : public subClass{
    public:
        Transmutation() {}
        Transmutation(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
//cleric subclasses
class Life : public subClass{
    public:
        Life() {}
        Life(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
class Light : public subClass{
    public:
        Light() {}
        Light(string name, vector<tuple<int, string, string>> subClassFeatures){
            this->name = name;
            this->subClassFeatures = subClassFeatures;
        }
};
#endif // CHARACTERCLASS_H
