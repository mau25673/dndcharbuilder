#include "character.h"
#include <sstream>
#include <tuple>
using namespace std;
void Character::SetScore(int str, int dex, int con, int inte, int wis, int cha){
    vector<tuple<string,int,int>> scores;
    scores.push_back(tuple("Strength", str, (str - 10) / 2));
    scores.push_back(tuple("Dexterity", dex, (dex - 10) / 2));
    scores.push_back(tuple("Constitution", con, (con - 10) / 2));
    scores.push_back(tuple("Intelligence", inte, (inte - 10) / 2));
    scores.push_back(tuple("Wisdom", wis, (wis - 10) / 2));
    scores.push_back(tuple("Charisma", cha, (cha - 10) / 2));
    this->scores = scores;
}

void Character::SetName(string name){
    this->name = name;
}
void Character::SetLevel(int level){
    this->level = level;
}
void Character::SetCharacterClass(characterClass charClass){
    this->charClass = charClass;
}
void Character::SetCharacterSubClass(subClass charSubClass){
    this->charSubClass = charSubClass;
}
void Character::SetBackground(Background background){
    this->background = background;
}
void Character::SetSpecies(Species charSpecies){
    this->charSpecies = charSpecies;
}

characterClass Character::GetCharacterClass() const{
    return this->charClass;
}
subClass Character::GetCharacterSubClass() const{
    return this->charSubClass;
}
Background Character::GetBackground() const{
    return this->background;
}
string Character::GetName() const{
    return this->name;
}
int Character::GetLevel() const{
    return this->level;
}
Species Character::GetSpecies() const{
    return this->charSpecies;
}
string Character::GetScore() const{
    stringstream stream;
    for (size_t i = 0; i < this->scores.size(); i++){
        stream << get<1>(this->scores.at(i)) << "|";
    }
    return stream.str();
}
vector<tuple<string,int,int>> Character::GetScoreRaw() const{
    return this->scores;
}
