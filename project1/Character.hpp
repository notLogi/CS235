//Roger Su
//CSCI-235
//Project 1


#ifndef Character_hpp
#define Character_hpp
#include <string>
#include <iostream>
class Character{
   enum Race {NONE, HUMAN, ELF, DWARF, LIZARD, UNDEAD};
   public:
   Character(); //default constructor
   Character(std::string name, std::string race, int vitality = 0, 
   int armor = 0, int level = 0, bool enemy = false); // This is the paramatized constructor
   void setName(const std::string& name);
   std::string getName() const;
   void setRace(const std::string& race);
   std::string getRace() const;
   void setVitality(const int &vitality);
   int getVitality() const;
   void setArmor(const int &armor);
   int getArmor() const;
   void setLevel(const int &level);
   int getLevel() const;
   void setEnemy();
   bool isEnemy() const;
   private:
   std::string name_; //Name of the character
   Race race_; // Race of a character through the use of enum
   int vitality_;// Vitality of the character
   int armor_; // Armor value of the character
   int level_; // Level value of the character
   bool enemy_; //If the character is hostile or not

};
#endif
