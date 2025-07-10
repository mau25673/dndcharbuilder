#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <string>

using namespace std;

class Background
{
private:
    string name;
    string description;
    string feature;
public:
    Background(){}
    Background(string name, string description, string feature){
        this->name = name;
        this->description = description;
        this->feature = feature;
    }
    string getName() const { return name; }
    string getDescription() const { return description; }
    string getFeature() const { return feature; }
};

#endif // BACKGROUND_H
