#ifndef Mage_hpp
#define Mage_hpp

#include "Character.hpp"
#include <iostream>
#include <string>
#include <cctype>



class Mage : public Character{
public:
    Mage();//default accessor
    Mage(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, const std::string& school_of_magic = "NONE", const std::string& weapon = "NONE", bool can_summon_incarnate = false); //parameterized constructor 
    bool setSchool(const std::string& school_of_magic); //the mutator function for school
    std::string getSchool() const; //the accessor for school
    bool setCastingWeapon(const std::string& weapon);//allows you to change the weapon
    std::string getCastingWeapon() const;//allows you to get the weapon 
    void setIncarnateSummon(const bool& summon); //can set the boolean to true or false to indicate if the character able to summon or not.
    bool hasIncarnateSummon() const; //returns the boolean value
private:
    std::string school_of_magic_; //string that stores the school
    std::string weapon_; //string that stores the weapon
    bool can_summon_incarnate_; //stores the bool that indicates if the mage is able to summon or not.
};
#endif  