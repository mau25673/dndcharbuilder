#include "characterclass.h"

using namespace std;

characterClass::characterClass() {}

string characterClass::getFeatureName(size_t index) const{
    return get<1>(this->features.at(index));
}
int characterClass::getFeatureLevel(size_t index) const{
    return get<0>(this->features.at(index));
}
string characterClass::getFeatureDescription(size_t index) const{
    return get<2>(this->features.at(index));
}
vector<tuple<int, string, string>> characterClass::getFeatures() const{
    return this->features;
}

void characterClass::setName(string name){
    this->name = name;
}

void rogueClass::SetSneakAttack(pair<int,int> sneakAttack){
    this->sneakAttack = sneakAttack;
}
pair<int,int> rogueClass::GetSneakAttack() const{
    return this->sneakAttack;
}

void clericClass::SetSpellList(vector<tuple<int,string,string>> spellList){
    this->spellList = spellList;
}
void clericClass::SetSpellSlots(vector<pair<int,int>> spellSlots){
    this->spellSlots = spellSlots;
}

vector<tuple<int,string,string>> clericClass::GetSpellList(){
    return this->spellList;
}

void wizardClass::SetSpellList(vector<tuple<int,string,string>> spellList){
    this->spellList = spellList;
}
void wizardClass::SetSpellSlots(vector<pair<int,int>> spellSlots){
    this->spellSlots = spellSlots;
}

vector<tuple<int,string,string>> wizardClass::GetSpellList(){
    return this->spellList;
}

// SUBCLASSES  -----------

string subClass::GetName() const{
    return this->name;
}
string subClass::getFeatureName(size_t index) const{
    return get<1>(this->subClassFeatures.at(index));
}
int subClass::getFeatureLevel(size_t index) const{
    return get<0>(this->subClassFeatures.at(index));
}
string subClass::getFeatureDescription(size_t index) const{
    return get<2>(this->subClassFeatures.at(index));
}
vector<tuple<int, string, string>> subClass::getFeatures() const{
    return this->subClassFeatures;
}
