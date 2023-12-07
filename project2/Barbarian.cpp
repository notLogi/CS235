#include "Barbarian.hpp"
#include <iostream>

/*
    Default constructor.
    Default-initializes all private members. Default character name: "NAMELESS". 
    Booleans are default-initialized to False. 
    Default weapons: "NONE". 
*/
Barbarian::Barbarian() : Character(){
    main_weapon_ = "NONE";
    secondary_weapon_ = "NONE";
    enraged_ = false;
}
/*  t
    Parameterized constructor.
    @param      : The name of the character (a const string reference)
    @param      : The race of the character (a const string reference)
    @param      : The character's vitality (an integer). Default to 0
    @param      : The character's max armor level (an integer). Default to 0
    @param      : The character's level (an integer). Default to 0
    @param      : A flag indicating whether the character is an enemy. Default to false
    @param      : The character's main weapon (a const string reference). 
                  String inputs can be in lowercase, but must be converted to uppercase 
                  when setting the variable. Only alphabetical characters are allowed.
                  Default to "NONE"
    @param      : The character's offhand weapon (a const string reference). 
                  String inputs can be in lowercase, but must be converted to uppercase 
                  when setting the variable. Only alphabetical characters are allowed.
                  Default to "NONE"
    @param      : A flag indicating whether the character is enraged. Default to false
    @post       : The private members are set to the values of the corresponding parameters. 
                : If the main and secondary weapons are not provided or invalid, the variables                    are set to "NONE".
*/
Barbarian::Barbarian(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, const std::string& main, const std::string& secondary,bool enraged) : Character(name, race, vitality, armor, level, enemy){
    setMainWeapon(main);
    setSecondaryWeapon(secondary);
    setEnrage(enraged);
    if (setMainWeapon(main) == false && setSecondaryWeapon(secondary) == false){
        main_weapon_ = "NONE";
        secondary_weapon_ = "NONE";
    }
}
/*
    @param    : a reference to a string representing the Character's main weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
                If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.
*/
bool Barbarian::setMainWeapon(const std::string& main){
    std::string main_uppercased = "";
    for(int i = 0; i < main.length(); i++){
        if(!std::isalpha(main[i])){
            return false;
        }
        else if(std::isalpha(main[i])){
            main_uppercased += std::toupper(main[i]);
        }
    }
    main_weapon_ = main_uppercased;
    return true;
}
/*
    @return   : a string of the Character's main weapon
*/
std::string Barbarian::getMainWeapon() const{
    return main_weapon_;
}
/*
    @param    : a reference to a string representing the Character's secondary weapon
    @post     : sets the private member variable to the value of the parameter. 
                Only alphabetical characters are allowed.
                String inputs can be in lowercase, but must be converted to uppercase when 
                setting the variable.
              : If the given input is invalid (i.e contains numbers), do nothing and return false
    @return   : true if setting the variable was successful, false otherwise.
*/
bool Barbarian::setSecondaryWeapon(const std::string& secondary){
        std::string secondary_uppercased = "";
    for(int i = 0; i < secondary.length(); i++){
        if(!std::isalpha(secondary[i])){
            return false;
        }
        else if(std::isalpha(secondary[i])){
            secondary_uppercased += std::toupper(secondary[i]);
        }
    }
    secondary_weapon_ = secondary_uppercased;
    return true;
}
/*
   @return    : a string of the Character's secondary weapon
*/
std::string Barbarian::getSecondaryWeapon() const{
    return secondary_weapon_;
}
/*
  @param      : a reference to a bool
  @post       : sets the private member variable to the value of the parameter.
*/
void Barbarian::setEnrage(const bool& enrage){
    enraged_ = enrage;
}
/*
  @return  : a boolean of whether the Character is enraged
*/
bool Barbarian::getEnrage() const{
    return enraged_;
}
/*
  @post   : sets the enraged variable to the opposite of what it was
*/
void Barbarian::toggleEnrage(){
    enraged_ = !enraged_;
}
