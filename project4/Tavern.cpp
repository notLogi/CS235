/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Georgina Woo
June 20 2023
Tavern.cpp declares the Tavern class along with its private and public members
*/
#include "Tavern.hpp"

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}
    /**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
1. Name: An uppercase string
2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
4. Level/Vitality/Armor: A positive intetger
5. Enemy: 0 (False) or 1 (True)
6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/
Tavern::Tavern(const std::string& fileName){
  std::ifstream file(fileName);
  if(!file.is_open()){
    std::cerr << "Invalid file " << fileName << std::endl;
    return;
  }
  std::string line, hold, name, race, subclass, main, arrowtype, offhand, schoolORfaction, affinity, affinityHold;
  int number, level, vitality, armor, arrowquantity;
  bool enemy, summon, disguise, enraged;
  while(std::getline(file, line)){
    std::istringstream isString(line); //streams the sentence
    std::vector<Arrows> arrowList;
    std::vector<std::string> affinityList;
    std::getline(isString, hold, ',');
    name = hold;
    std::getline(isString, hold, ',');
    race = hold;
    std::getline(isString, hold, ',');
    subclass = hold;
    std::getline(isString, hold, ',');
    std::istringstream LevelNum(hold);//uses another variable to hold the string and coverts it to integer.
    LevelNum >> level;
    std::getline(isString, hold, ',');
    std::istringstream VitalityNum(hold);
    VitalityNum >> vitality;
    std::getline(isString, hold, ',');
    std::istringstream ArmorNum(hold);
    ArmorNum >> armor;
    std::getline(isString, hold, ',');
    std::istringstream theEnemy(hold);//same concept with the integers but for booleans.
    theEnemy >> enemy;
    if (subclass == "RANGER"){//if it is ranger, it will have another stringstream inside the stringstream.
      std::getline(isString, hold, ',');
      arrowtype = hold;
      std::istringstream arrowInfoStream(arrowtype);
      std::string arrowInfo;
      while (std::getline(arrowInfoStream, arrowInfo, ';')) {
        std::istringstream arrowTypeQuantityStream(arrowInfo);
        Arrows arrows;
        arrowTypeQuantityStream >> arrows.type_ >> arrows.quantity_;
        arrowList.push_back(arrows);
      }
    } 
    else {
    // For other subclasses (Barbarian, Mage, Scoundrel), simply read the "Main" attribute
      std::getline(isString, hold, ',');
      main = hold;
    }
    std::getline(isString,hold, ',');
    offhand = hold;

    std::getline(isString, hold, ',');
    schoolORfaction = hold;

    std::getline(isString, hold, ',');
    std::istringstream Summon_Able(hold);
    Summon_Able >> summon;

    std::getline(isString, hold, ',');//same concept for affinities with the arrows
    if (subclass == "RANGER") {
      affinity = hold;
      std::istringstream affinityInfoStream(affinity);
      std::string affinityInfo;
      while (std::getline(affinityInfoStream, affinityInfo, ';')) {
        affinityList.push_back(affinityInfo);
      }
    } 
    else {
      affinityHold = "NONE"; // Set to "NONE" for non-RANGER subclasses
    }
    std::getline(isString, hold, ',');
    std::istringstream Disguise_Able(hold);
    Disguise_Able >> disguise;
      
    std::getline(isString, hold, ',');
    std::istringstream Enraged_Able(hold);
    Enraged_Able >> enraged;
      
    if(subclass == "MAGE"){//want to initialize pointers for each subclass and then increment them by calling enterTavern()
      Character * mage = new Mage(name, race, vitality, armor, level, enemy, schoolORfaction, main, summon);
      enterTavern(mage);
    }
    else if(subclass == "BARBARIAN"){
      Character * barbarian = new Barbarian(name, race, vitality, armor, level, enemy, main, offhand, enraged);
      enterTavern(barbarian);
    }
    else if(subclass == "RANGER"){
      Character * ranger = new Ranger(name, race, vitality, armor, level, enemy, arrowList, affinityList, summon);
      enterTavern(ranger);
    }
    else if(subclass == "SCOUNDREL"){
      Character * scoundrel = new Scoundrel(name, race, vitality, armor, level, enemy, main, schoolORfaction, disguise);
      enterTavern(scoundrel);
    }
    arrowList.clear();
    affinityList.clear();
  }
  file.close();
}

/** 
    @param:   A reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character* a_character)
{
  if(add(a_character))
  {
    level_sum_ += a_character->getLevel();
    if(a_character->isEnemy()){
      num_enemies_++;
      return true;
    }
  }
  return false; 
}

/** @param:   A reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
    **/
    int Tavern::getLevelSum()
    {
      return level_sum_;
    }



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}
/**
    @post: For every character in the tavern, displays each character's information
*/
    
void Tavern::displayCharacters() const{//due to polymorphism, whatever the object type is for each item, it will use the functions overridden in that subclass.
  for(int i = 0; i < item_count_; i++){
    items_[i]->display();
  }
}
/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information

*/
void Tavern::displayRace(const std::string& race) const {//same concept with this class.
  for (int i = 0; i < item_count_; i++) {
    if (items_[i]->getRace() == race) {
      items_[i]->display();
    }
  }
}

/**
    @post: Every character in the tavern eats a tainted stew.
*/
void Tavern::taintedStew() {//same concept with this class.
    for (int i = 0; i < item_count_; i++) {
        items_[i]->eatTaintedStew();
    }
}
