#include "Scoundrel.hpp"
#include <iostream>
/*
    Default constructor.
    Default-initializes all private members. 
    Default character name: "NAMELESS". Booleans are default-initialized to False. 
    Default dagger: WOOD. Default faction: "NONE". 
*/
Scoundrel::Scoundrel() : Character(){
    dagger_ = WOOD;
    faction_ = "NONE";
    has_disguise_ = false;
}
/*
    Parameterized constructor.
    @param      : The name of the character (a const string reference)
    @param      : The race of the character (a const string reference)
    @param      : The character's vitality (an integer). Default to 0
    @param      : The character's max armor level (an integer). Default to 0
    @param      : The character's level (an integer). Default to 0
    @param      : A flag indicating whether the character is an enemy. Default to false.
    @param      : The character's dagger type (a const string reference).
                  String inputs can be in lowercase, but must be converted to 
                  uppercase when setting the dagger enum. Default to WOOD
    @param      : The character's Faction (a const string reference). 
                  Valid Factions: [CUTPURSE, SHADOWBLADE, SILVERTONGUE] 
                  String inputs can be in lowercase, but must be converted to 
                  uppercase when setting the variable. Default to "NONE"
    @param      : A flag indicating whether the character has a disguise. Default to false
    @post       : The private members are set to the values of the corresponding 
                  parameters.
                 If the dagger type is not provided or invalid, the variable should 
                  be set to WOOD. 
                 If the Faction is not provided or invalid, the variable should be 
                  set to "NONE". 
*/
Scoundrel::Scoundrel(const std::string& name, const std::string& race, int vitality, int armor, int level, bool enemy, const std::string& dagger, const std::string& faction, bool disguise) : Character(name, race, vitality, armor, level, enemy){
    setDagger(dagger);
    setFaction(faction);
    setDisguise(disguise);
}
/*
   @param     : a reference to a string representing the dagger type
   @post      : sets the private member variable to the value of the parameter. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the dagger type is not valid (i.e, is one of the following: 
                [WOOD, BRONZE, IRON, STEEL, MITHRIL, ADAMANT, RUNE]), 
                the variable should be set to WOOD. 
*/
void Scoundrel::setDagger(const std::string& dagger){
    std::string dagger_uppercased = "";
    for(int i = 0; i < dagger.length(); i++){
        if(std::isalpha(dagger[i])){
            dagger_uppercased += std::toupper(dagger[i]);
        }
    }
    if(dagger_uppercased == "WOOD"){
        dagger_ = WOOD;
    }
    else if(dagger_uppercased == "BRONZE"){
        dagger_ = BRONZE;
    }
    else if(dagger_uppercased == "IRON"){
        dagger_ = IRON;
    }
    else if(dagger_uppercased == "STEEL"){
        dagger_ = STEEL;
    }
    else if(dagger_uppercased == "MITHRIL"){
        dagger_ = MITHRIL;
    }
    else if(dagger_uppercased == "ADAMANT"){
        dagger_ = ADAMANT;
    }
    else if(dagger_uppercased == "RUNE"){
        dagger_ = RUNE;
    }
    else{
        dagger_ = WOOD;
    }
}
/*
  @return : the string indicating the character's dagger type
*/
std::string Scoundrel::getDagger() const{
    if(dagger_ == Dagger::WOOD){
        return "WOOD";
    }
    else if(dagger_ == Dagger::BRONZE){
        return "BRONZE";
    }
    else if(dagger_ == Dagger::IRON){
        return "IRON";
    }
    else if(dagger_ == Dagger::STEEL){
        return "STEEL";
    }
    else if(dagger_ == Dagger::MITHRIL){
        return "MITHRIL";
    }
    else if(dagger_ == Dagger::ADAMANT){
        return "ADAMANT";
    }
    else if(dagger_ == Dagger::RUNE){
        return "RUNE";
    }
    else{
        return "WOOD";
    }
}
/*
    @param    : a reference to a string representing the character's Faction
    @post     : sets the private member variable to the value of the parameter. 
                String inputs can be in lowercase, but must be converted to 
                uppercase when setting the variable.
                If the provided faction is not one of the following: 
               [NONE, CUTPURSE, SHADOWBLADE, SILVERTONGUE], 
               do nothing and return false.
    @return   : true if setting the variable was successful, false otherwise.
*/
bool Scoundrel::setFaction(const std::string& faction){
    std::string faction_uppercased = "";
    for(int i = 0; i < faction.length(); i++){
        if(std::isalpha(faction[i])){
            faction_uppercased += std::toupper(faction[i]);
        }
    }
    if(faction_uppercased == "NONE" || faction_uppercased == "CUTPURSE" || faction_uppercased == "SHADOWBLADE" || faction_uppercased == "SILVERTONGUE"){
        faction_ = faction_uppercased;
        return true;
    }
    return false;
}
/*
  @return  : the string indicating the character's Faction
*/
std::string Scoundrel::getFaction() const{
    return faction_;
}
/*
  @param  : a reference to boolean
  @post   : sets the private member variable indicating whether the character has a disguise
*/
void Scoundrel::setDisguise(const bool& disguise){
    if(disguise == true){
        has_disguise_ = true;
    }
    else if(disguise == false){
        has_disguise_ = false;
    }
}
/*
  @return  : the disguise flag
*/
bool Scoundrel::hasDisguise() const{
    if (has_disguise_ == true){
        return true;
    }
    return false;
}