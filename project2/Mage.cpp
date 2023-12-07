#include "Mage.hpp"
#include <iostream>
/**
  Default constructor.
  Default-initializes all private members. 
  Default character name: "NAMELESS". Booleans are default-initialized to False. 
  Default school of magic and weapon: "NONE". 
*/
Mage::Mage():Character(){//done
    school_of_magic_ = "NONE";
    weapon_ = "NONE";
    can_summon_incarnate_ = false;
}
/*
  Parameterized constructor.
  @param      : The name of the character (a const string reference)
  @param      : The race of the character (a const string reference)
  @param      : The character's vitality (an integer). Default to 0
  @param      : The character's max armor level (an integer). Default to 0
  @param      : The character's level (an integer). Default to 0
  @param      : A flag indicating whether the character is an enemy. Default to false.
  @param      : The character's school of magic (a const string reference). Valid schools: 
                [ELEMENTAL, NECROMANCY, ILLUSION]. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable. Default to "NONE".
  @param      : The character's choice of weapon (a const string reference). 
                Valid weapons: [WAND, STAFF]
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable. Default to "NONE".
  @param      : A flag indicating whether the character is able to summon an 
                incarnate. Default to false.
  @post       : The private members are set to the values of the corresponding 
                parameters.
                REMEMBER: If the school of magic or weapon is not provided or invalid, the 
                variables should be set to "NONE". 
*/
Mage::Mage(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, const std::string& school_of_magic, const std::string& weapon, bool summon) :
Character(name, race, vitality, armor, level, enemy){
    
    setSchool(school_of_magic); //calls the functions so it doesn't have to be written twice
    setCastingWeapon(weapon);
    setIncarnateSummon(summon);
    if(setSchool(school_of_magic) == false){
        school_of_magic_ = "NONE";
    }
    if(setCastingWeapon(weapon) == false){
        weapon_ = "NONE";
    }
}   

/*
    @param  : a reference to a string representing the school of magic
    @post   : sets the private member variable to the value of the parameter. If 
              the provided school of magic is not one of the following: [ELEMENTAL, 
              NECROMANCY, ILLUSION], do nothing and return false.
              String inputs can be in lowercase, but must be converted to 
              uppercase when setting the variable.
    @return  : true if setting the variable was successful, false otherwise.
*/
bool Mage::setSchool(const std::string& school_of_magic){ //done  
    std::string school_of_magic_uppercased = "";
    for (auto c : school_of_magic){
        if(std::isalpha(c)){
            school_of_magic_uppercased += toupper(c);
        }
    }
    if (school_of_magic_uppercased == "ELEMENTAL"){
        school_of_magic_ = school_of_magic_uppercased;
        return true;
    }
    else if(school_of_magic_uppercased == "NECROMANCY"){
        school_of_magic_ = school_of_magic_uppercased;
        return true;
    }
    else if(school_of_magic_uppercased == "ILLUSION"){
        school_of_magic_ = school_of_magic_uppercased;
        return true;
    }
    return false;
}
/*
  @return  : the string indicating the character's school of magic
*/
std::string Mage::getSchool() const{//done
    return school_of_magic_;
}
/*
    @param  : a reference to a string representing the character's weapon
    @post   : sets the private member variable to the value of the parameter.
              String inputs can be in lowercase, but must be converted to 
              uppercase when setting the variable.
              If the provided weapon is not one of the following: 
              [WAND, STAFF], do nothing and return false.
    @return  : true if setting the variable was successful, false otherwise.
*/
bool Mage::setCastingWeapon(const std::string& weapon){
    std::string weapon_uppercased = "";
    for(auto c : weapon){
        if(isalpha(c)){
            weapon_uppercased += toupper(c);
        }
    }   
    if(weapon_uppercased == "WAND"){
        weapon_ = weapon_uppercased;
        return true;
    }
    else if(weapon_uppercased == "STAFF"){
        weapon_ = weapon_uppercased;
        return true;
    }
    return false;
}
/*
  @return  : the string indicating the character's weapon
*/
std::string Mage::getCastingWeapon() const{//done
    return weapon_;
}
/*
  @param  : a reference to boolean
  @post   : sets the private member variable indicating whether the character can 
            summon an incarnate
*/
void Mage::setIncarnateSummon(const bool& summon){//done
    can_summon_incarnate_ = summon;
}
/*
  @return  : the summon-incarnate flag
*/
bool Mage::hasIncarnateSummon() const{//done
    return can_summon_incarnate_;
}