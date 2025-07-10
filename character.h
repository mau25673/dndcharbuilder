#ifndef CHARACTER_H
#define CHARACTER_H
#include "background.h"
#include "characterclass.h"
#include "species.h"
#include <string>
#include <tuple>
#include <vector>
using namespace std;
class Character{
    private:
        string name;
        characterClass charClass;
        subClass charSubClass;
        Species charSpecies;
        Background background;
        int level;
        vector<tuple<string,int,int>> scores;
        vector<tuple<string,int,string>> skills;
    public:
        Character(){};
        Character(string name, characterClass charClass, subClass charSubClass, Background background, Species charSpecies, int level, int str, int dex, int con, int inte, int wis, int cha){
            vector<tuple<string,int,int>> scores;
            vector<tuple<string,int,string>> skills;
            this->name = name;
            this->charClass = charClass;
            this->level = level;
            this->charSpecies = charSpecies;
            this->background = background;
            this->charSubClass = charSubClass;
            vector<string> namesScores = {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
            vector<int> valuesScores = { str, dex, con, inte, wis, cha };
            for (size_t i = 0; i < namesScores.size(); i++) {
                int modifier = (valuesScores[i] - 10) / 2;
                scores.push_back(make_tuple(namesScores[i], valuesScores[i], modifier));
            }

            vector<string> namesSkills = {"Athletics", "Acrobatics", "Sleight of Hand", "Stealth", "Arcana", "History",
            "Investigation", "Nature", "Religion", "Animal Handling", "Insight", "Medicine", "Perception", "Survival",
            "Deception", "Intimidation", "Performance", "Persuasion"};
            vector<int> valuesSkills = {str, dex, dex, dex, inte, inte, inte, inte, inte, wis, wis, wis, wis, wis, cha, cha, cha, cha};
            for (size_t i = 0; i < namesSkills.size(); i++) {
                int modifier = (valuesSkills[i] - 10) / 2;
                skills.push_back(make_tuple(namesSkills[i], modifier, "None"));
            }

            this->scores = scores;
            this->skills = skills;
        }
        void SetName(string name);
        void SetCharacterClass(characterClass charClass);
        void SetCharacterSubClass(subClass charSubClass);
        void SetBackground(Background Background);
        void SetLevel(int level);
        void SetScore(int str, int dex, int con, int inte, int wis, int cha);
        void SetSpecies(Species charSpecies);

        characterClass GetCharacterClass() const;
        subClass GetCharacterSubClass() const;
        Background GetBackground() const;
        Species GetSpecies() const;
        string GetName() const;
        string GetScore() const;
        vector<tuple<string,int,int>> GetScoreRaw() const;
        int GetLevel() const;
};

#endif // CHARACTER_H
