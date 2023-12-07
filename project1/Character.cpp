//Roger Su
//CS235
//Project 1
#include "Character.hpp"

/*
  Default constructor.
  Default-initializes all private members. 
  Default character name: "NAMELESS". 
  Booleans are default-initialized to False. 
  Default enum value: NONE. 
  Default Vitality, Max Armor, and Level: 0.
*/
Character::Character(){ //Done
    name_ = "NAMELESS";
    race_ = NONE;
    vitality_ = 0;
    armor_ = 0;
    level_ = 0;
    enemy_ = false;
}
/*
  Parameterized constructor.
  @param      : The name of the character (a string in UPPERCASE)
  @param      : The race of the character (a string)
  @param      : The character's vitality (a non-negative integer) , with default  
                value 0
  @param      : The character's max armor level (a non-negative integer), with 
                default value 0
  @param      : The character's level (non-negative integer), with default value 0
  @param      : A flag indicating whether the character is an enemy, with default 
                value false
  @post       : The private members are set to the values of the corresponding 
                parameters.
*/
Character::Character( std::string name, std::string race, int vitality, 
int armor, int level, bool enemy){
    name_ = "";
    for (auto c : name) {               //Here, we check each individual character. 
        if (isalpha(c)) {               //With a range based loop called "c"
            name_ += toupper(c);        //Checks if the character is an alphabet,
        }                                
    }  
    if (name_ == ""){ //If there's no valid characters, it will be named to NAMELESS
        name_ = "NAMELESS";
    }
    if (race == "HUMAN") { 
        race_ = HUMAN;
    } else if (race == "ELF") {
        race_ = ELF;
    } else if (race == "DWARF") {
        race_ = DWARF;
    } else if (race == "LIZARD") {
        race_ = LIZARD;
    } else if (race == "UNDEAD") {
        race_ = UNDEAD;
    } else {
        race_ = NONE; 
    }
    if (vitality >= 0){
    vitality_ = vitality;
    }
    if(armor >= 0){
        armor_ = armor;
    }
    if(level >= 0){
        level_ = level;
    }
    enemy_ = enemy;     
}
    /*
    @param  : the name of the Character
    @post   : sets the Character's title to the value of the parameter, 
    in UPPERCASE. Only alphabetical characters are allowed. 
    For example, attempting to create a character named 
    "TW3EDLEDUM2" should create a character named "TWEDLEDUM".
    : If the given parameter does not have any valid alphabetical
    characters, the character's name should be set to "NAMELESS".
*/
void Character::setName(const std::string& name) {
    name_ = "";
    for (auto c : name) {               //Here, we check each individual character. 
        if (isalpha(c)) {               //With a range based loop called "c"
            name_ += toupper(c);        //Checks if the character is an alphabet,
        }                               //If so, then it makes the character 
    }                                   //uppercase if it is lowercase.
    if (name_ == "") {
        name_ = "NAMELESS";
    }
        }
std::string Character::getName() const{//Basically returns the name
    return name_;
}
    /*This will take in a string from the user input or whenever the function is 
    called and if the race matches one of the enums, then it will set it to that
    race, but if it is anything else, it will be "NONE"*/
void Character::setRace(const std::string& race){
        if (race == "HUMAN") {
            race_ = HUMAN;
        } else if (race == "ELF") {
            race_ = ELF;
        } else if (race == "DWARF") {
            race_ = DWARF;
        } else if (race == "LIZARD") {
            race_ = LIZARD;
        } else if (race == "UNDEAD") {
            race_ = UNDEAD;
        } else {
            race_ = NONE; 
        }
    }
/*
      @return : the race of the Character (a string)
      If race_ equals a certain enum, then it will return the string.
*/
    std::string Character::getRace() const{
        if (race_ == HUMAN){
            return "HUMAN";
        }
        else if (race_ == ELF){
            return "ELF";
        }
        else if (race_ == DWARF){
            return "DWARF";
        }
        else if (race_ == LIZARD){
            return "LIZARD";
        }
        else if (race_ == UNDEAD){
            return "UNDEAD";
        }
            return "NONE";
    }
      /*
    @param  : an integer vitality
    @pre    : vitality >= 0 : Characters cannot have negative health
    @post   : sets the vitality private member to the value of the parameter
  */
void Character::setVitality(const int& vitality){//true
    if (vitality >= 0){
        vitality_ = vitality;//basically changes the vitality
    }
}
/*
      @return : the value stored in vitality_
*/
int Character::getVitality() const{ //true
    return vitality_;//if the user wants to see the vitality, they can use this.
}
  /*
    @param  : an integer armor level
    @pre    : armor >= 0 : Characters cannot have negative armor
    @post   : sets the armor private member to the value of the parameter
  */
void Character::setArmor(const int& armor){ //true
    if(armor >= 0){
        armor_ = armor;                 //changes the armor value
    }   
}
  /*
      @return : the value stored in armor_
   */
int Character::getArmor() const{ //true
    return armor_;
}
 /*
    @param  : an integer level
    @pre    : level >= 0 : Characters cannot have a negative
    @post   : sets the level private member to the value of the parameter
  */
void Character::setLevel(const int& level){ //true
    if(level >= 0){
        level_ = level;             //changes the level
    }
}

  /*
      @return : the value stored in level_
   */
int Character::getLevel() const{ //true
    return level_;
}
  /*
   @post   : sets the enemy flag to true
  */
void Character::setEnemy(){ //true
    enemy_ = true;              //sets the character "made" to an enemy 
}
/*
    @return true if the character is an enemy, false otherwise

    Note: this is an accessor function and must follow the same convention as all accessor  
          functions even if it is not called getEnemy
*/
bool Character::isEnemy() const{
    return enemy_; //Done
}
