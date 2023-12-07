#include "Tavern.hpp"
/**
    Default constructor.
    Default-initializes all private members. 
*/
Tavern::Tavern() : ArrayBag<Character>(){
    total_enemies_ = 0;
    total_level_ = 0;
}
/** @param:   A const reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to the tavern (i.e. items_),                 false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count 
              if the character is an enemy.
 **/
bool Tavern::enterTavern(const Character& character){
    if(!contains(character)){
        add(character);
        total_level_ += character.getLevel();
        if(character.isEnemy()){
            total_enemies_++;
        }
        return true;
    }
    return false;
}
/** @param:   A const reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from the tavern (i.e. items_),               false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count
              if the character is an enemy.
 **/
bool Tavern::exitTavern(const Character& character){
    if(contains(character)){
        remove(character);
        total_level_ -= character.getLevel();
        if(character.isEnemy()){
            total_enemies_--;
        }
        return true;
    }
    return false;
}

/** 
    @return:  The integer level count of all the characters currently in the Tavern
 **/
int Tavern::getLevelSum() const{
    return total_level_;
}

/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Computes the average level of the Tavern rounded to the NEAREST integer.
 **/
int Tavern::calculateAvgLevel() const{
    double levelSum = total_level_;
    double characterSum = item_count_;
    double avgLevel = levelSum/characterSum;
    int roundedavgLevel = int(avgLevel);
    return roundedavgLevel;
}
/** 
    @return:  The integer enemy count of the Tavern
 **/
int Tavern::getEnemyCount() const{
    return total_enemies_;
}
/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Computes the enemy percentage of the Tavern rounded up to 2 decimal places.
 **/
double Tavern::calculateEnemyPercentage() const{
    double characterSum = item_count_;
    double enemySum = total_enemies_;
    double enemyPercentage = enemySum/characterSum;
    return std::round(enemyPercentage * 100 * 100) / 100;
}

/** 
    @param:   A const reference to a string representing a character Race with value in 
              ["NONE", "HUMAN", "ELF", "DWARF", "LIZARD", "UNDEAD"]
    @return:  An integer tally of the number of characters in the Tavern of the given race. 
              If the argument string does not match one of the expected race values, 
              the tally is zero. NOTE: no pre-processing of the input string necessary, only                  uppercase input will match.
 **/
int Tavern::tallyRace(const std::string& race){
    int total = 0;
    for(int i = 0; i <item_count_; i++){
        if(race == items_[i].getRace()){
            total++;
        }
    }
    return total;
}
/**
@post:      Outputs a report of the characters currently in the tavern in the form:
            "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average             level is: [x] \n[x]% are enemies.\n"
            Note that the average level should be rounded to the NEAREST integer, and the enemy             percentage should be rounded to 2 decimal places.

            Example output: 
            Humans: 3
            Elves: 5
            Dwarves: 8
            Lizards: 6
            Undead: 0

            The average level is: 7
            46.67% are enemies.
*/
void Tavern::tavernReport(){
    std::cout << "Humans: " << tallyRace("HUMAN")
    << " \nElves: " << tallyRace("ELF")
    << " \nDwarves: " << tallyRace("DWARF")
    << " \nLizards: " << tallyRace("LIZARD") 
    << " \nUndead: " << tallyRace("UNDEAD")
    << " \n\nThe average level is: " << calculateAvgLevel() << " \n"
    << calculateEnemyPercentage() << "% are enemies.\n";
}