#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include <string>
#include <utility>
using namespace std;

class Species
{
    protected:
        string name;
        string features;
        vector<pair<string,int>> abilityScores;
    public:
        Species() {}
        Species(string name, string features, int str, int dex, int con, int inte, int wis, int cha) {
            this->name = name;
            this->features = features;
            vector<pair<string,int>> Scores;
            vector<string> namesScores = {"Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma"};
            vector<int> valuesScores = { str, dex, con, inte, wis, cha };
            for (size_t i = 0; i < namesScores.size(); i++) {
                Scores.push_back(make_pair(namesScores[i], valuesScores[i]));
            }
            this->abilityScores = Scores;
        }
        Species(string name, string features, vector<pair<string,int>> abilityScores) {
            this->name = name;
            this->features = features;
            this->abilityScores = abilityScores;
        }

        void SetName(string name);
        void SetFeatures(string features);
        void SetAbilityScores(int str, int dex, int con, int inte, int wis, int cha);

        string GetName() const;
        string GetFeatures() const;
        vector<pair<string,int>> GetAbilityScores() const;
};

#endif // SPECIES_H
