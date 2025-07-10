#include "species.h"
#include <vector>
#include <utility>
void Species::SetName(string name){
    this->name = name;
}
void Species::SetFeatures(string features){
    this->features = features;
}
void Species::SetAbilityScores(int str, int dex, int con, int inte, int wis, int cha){
    vector<pair<string,int>> abilityScores;
    vector<string> namesScores = {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
    vector<int> valuesScores = { str, dex, con, inte, wis, cha };
    for (size_t i = 0; i < namesScores.size(); i++) {
        abilityScores.push_back(make_pair(namesScores[i], valuesScores[i]));
    }
    this->abilityScores = abilityScores;
}

string Species::GetName() const{
    return this->name;
}
string Species::GetFeatures() const{
    return this->features;
}
vector<pair<string,int>> Species::GetAbilityScores() const{
    return this->abilityScores;
}
