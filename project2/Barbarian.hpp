#ifndef Barbarian_hpp
#define Barbarian_hpp
#include "Character.hpp"
#include <iostream>
#include <string>
#include <cctype>

class Barbarian : public Character{
public:
    Barbarian();//default constructor
    Barbarian(const std::string& name, const std::string& race, int vitality = 0, int armor = 0, int level = 0, bool enemy = false, const std::string& main = "NONE", const std::string& secondary = "NONE", bool enraged = false); //paramaterized constructor
    bool setMainWeapon(const std::string& main); // setters to main weapon
    std::string getMainWeapon() const; //getters for main weapon
    bool setSecondaryWeapon(const std::string& secondary);//setters for offhand
    std::string getSecondaryWeapon() const;//getter for offhand
    void setEnrage(const bool& enrage);//setter for enrage
    bool getEnrage() const; //getter for enrage
    void toggleEnrage();//if this is called then it will reverse the boolean
private:
    std::string main_weapon_;//string value for main weapon
    std::string secondary_weapon_;//string value of offhand
    bool enraged_;//boolean value for if character is enraged
};
#endif