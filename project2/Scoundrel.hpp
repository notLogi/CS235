#include "Character.hpp"
#include <string>
#include <cctype>
#include <iostream>
#ifndef Scoundrel_hpp
#define Scoundrel_hpp

class Scoundrel : public Character{
    enum Dagger {WOOD, BRONZE, IRON, STEEL, MITHRIL, ADAMANT, RUNE}; 
public:
    Scoundrel();//default constructor
    Scoundrel(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, const std::string& dagger = "WOOD", const std::string& faction = "NONE", bool disguise = false); //parameterized constructor
    void setDagger(const std::string& dagger); //setter for dagger
    std::string getDagger() const;//getter for dagger
    bool setFaction(const std::string& faction);//setter for faction
    std::string getFaction() const; //getter for faction
    void setDisguise(const bool& disguise);//setter for disguise
    bool hasDisguise() const;//getter for disguise
private:
    Dagger dagger_; //Enum value that stores dagger.
    std::string faction_;//string that stores the faction
    bool has_disguise_;//true or false if the character has a disguise
};

#endif