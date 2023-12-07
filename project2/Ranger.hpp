#include <iostream>
#include "Character.hpp"
#include <cctype>
#include <vector>
#include <string>
#ifndef Ranger_hpp
#define Ranger_hpp
struct Arrows //this structure is where type and quantity is stored through the vector "arrows_";
{
    std::string type_;
    int quantity_;
};
class Ranger : public Character{
public:
    Ranger();//default constructor
    Ranger(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, const std::vector<Arrows>& arrows = {}, const std::vector<std::string>& affinities = {}, bool recruit = false);//paramterized constructor
    bool addArrows(const std::string& type, int quantity);//setter for arrow type and quantity
    std::vector<Arrows> getArrows() const;//getter for arrow amount and type
    bool fireArrow(const std::string& firing);//fires the arrow if this is called
    bool addAffinity(const std::string& affinity);//setter for affinity
    std::vector<std::string> getAffinities() const;//getter for affinity
    void setCompanion(const bool& companion);//setter for companion
    bool getCompanion() const;//getter for companion
private:
    std::vector<Arrows> arrows_;//a vector array that stores both type and quantity for the structure.
    std::vector<std::string> affinities_;//a vector array that stores affinity.
    bool has_companion_;//a boolean value that determins if the class is able to get a companion.
};
#endif