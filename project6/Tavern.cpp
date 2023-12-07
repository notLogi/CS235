/*
CSCI235 Fall 2023
Project 3 - Tavern Class
Georgina Woo
June 20 2023
Taven.cpp declares the Tavern class along with its private and public members
Modified by Roger Su on 11/23/2023
*/
#include "Tavern.hpp"

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}



/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows:
      Name: An uppercase string
      Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
      Vitality/Armor/Level: A positive integer
      Enemy: 0 (False) or 1 (True)
    
    @post: Each line of the input file corresponds to a Character that enters the Tavern.
  */
    Tavern::Tavern(const std::string& filename)
    {
      std::ifstream fin(filename);
      std::string line;
      std::getline(fin, line);
      std::string name, race, string_vitality, string_armor, string_level, string_enemy;
      int vitality, armor, level;
      bool enemy;
      
      while(std::getline(fin, line))
      {
        std::istringstream iss(line);
        std::getline(iss, name, ',');
        std::getline(iss, race, ',');

        std::getline(iss, string_vitality, ',');
        std::istringstream(string_vitality) >> vitality;

        std::getline(iss, string_armor, ',');
        std::istringstream(string_armor) >> armor;

        std::getline(iss, string_level, ',');
        std::istringstream(string_level) >> level;

        std::getline(iss, string_enemy, ',');
        std::istringstream(string_enemy) >> enemy;
        Character* character = new Character(name, race, vitality, armor, level, enemy);
        enterTavern(character);
      }
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
    if(a_character->isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
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
void Tavern::displayCharacters()
{
  for(int i = 0; i < item_count_; i++)
  {
    items_[i]->display();
  }
}


/**
    @param: a string reference to a race
    @post: For every character in the tavern of the given race, displays each character's information
*/
void Tavern::displayRace(const std::string &race)
{
  for(int i = 0; i < item_count_; i++)
  {
    if(items_[i]->getRace() == race)
    {
      items_[i]->display();
    }
  }
}






/**
    @post: all characters leave the tavern
*/
void Tavern::emptyTavern()
{
  for(int i = 0; i < item_count_; i++)
  {
    delete items_[i];
    items_[i] = nullptr;
  }
  item_count_ = 0;
}
/**
  @param: a Character pointer 
  @post: sets the Tavern's main character to the pointer that is given
*/

void Tavern::setMainCharacter(Character* target){
  main_character_ = target;
}
/**
  @return: a pointer to the main character in the Tavern, nullptr if there is no main character
*/
Character* Tavern::getMainCharacter(){  
    return main_character_;
}
/**
  @param: two Character pointers
  @return: true if the lhs Character's level is less than the rhs Character's level
*/
bool Tavern::levelIsLess(Character* lhs, Character* rhs){
  return lhs->getLevel() < rhs->getLevel();
}
/**
  @param: two Character pointers
  @return: true if the lhs Character's level is greater than the rhs Character's level
*/
bool Tavern::levelIsGreater(Character* lhs, Character* rhs){
  return lhs->getLevel() > rhs->getLevel();
}
/**
  @param: two Character pointers
  @return: true if the lhs Character's vitality is less than the rhs Character's vitality
*/
bool Tavern::vitalityIsLess(Character* lhs, Character* rhs){
  return lhs->getVitality() < rhs->getVitality();
}
/**
  @param: two Character pointers
  @return: true if the lhs Character's vitality is more than the rhs Character's vitality
*/
bool Tavern::vitalityIsGreater(Character* lhs, Character* rhs){
  return lhs->getVitality() > rhs->getVitality();
}
/**
  @pre  : The combat queue should be emptied before the characters are added to the queue
  @param  : A string reference to a sorting filter with a default value of "NONE"
  @post   : With default filter "NONE": add every character marked as an enemy to the combat queue
    : With the filter "LVLASC": add every character in the Tavern marked as an enemy to the combat queue, in ascending order based on their level.
    : With the filter "LVLDES": add every character in the Tavern marked as an enemy to the combat queue, in descending order based on their level.
    : With the filter "HPASC": add every character in the Tavern marked as an enemy to the combat queue, in ascending order based on their vitality.
    : With the filter "HPDES": add every character in the Tavern marked as an enemy to the combat queue, in descending order based on their vitality.
*/
void Tavern::createCombatQueue(const std::string& filter){
  while(!combat_queue_.empty()){
    combat_queue_.pop();
  }
  std::vector<Character*> sorting;
  for(int i = 0; i < item_count_; i++){
    if(items_[i]->isEnemy()){
      sorting.push_back(items_[i]);
    }
  }
  if(filter == "NONE"){
    for(int i = 0; i < sorting.size(); i++){
      combat_queue_.push(sorting[i]);
    }
  }
else if (filter == "LVLASC") {
    std::sort(sorting.begin(), sorting.end(), [](Character* lhs, Character* rhs) {
        return lhs->getLevel() < rhs->getLevel();
    });
    for(int i = 0; i < sorting.size(); i++){
      combat_queue_.push(sorting[i]);
    }
}
  else if(filter == "LVLDES"){
    std::sort(sorting.begin(), sorting.end(), [](Character* lhs, Character* rhs){
      return lhs->getLevel() > rhs->getLevel();
    });
    for(int i = 0; i < sorting.size(); i++){
      combat_queue_.push(sorting[i]);
    }
  }
  else if(filter == "HPASC"){
    std::sort(sorting.begin(), sorting.end(), [](Character* lhs, Character* rhs){
      return lhs->getVitality() < rhs->getVitality();
    });
    for(int i = 0; i < sorting.size(); i++){
      combat_queue_.push(sorting[i]);
    }
  }
  else if(filter == "HPDES"){
    std::sort(sorting.begin(), sorting.end(), [](Character* lhs, Character* rhs){
      return lhs->getVitality() > rhs->getVitality();
    });
    for(int i = 0; i < sorting.size(); i++){
      combat_queue_.push(sorting[i]);
    }
  }
}

/**
  @post   : returns a pointer to the Character at the front of the Combat Queue. 
          : If there are no characters in the queue, return nullptr
*/
Character* Tavern::getTarget(){
  if(!combat_queue_.empty()){
    return combat_queue_.front();
  }
  else{
    return nullptr;
  }
}
/**
  @post : Prints the details of each character in the combat queue in the following form:
        : [ENEMY NAME]: LEVEL [ENEMY LEVEL] [ENEMY RACE]. \nVITALITY: [ENEMY VITALITY] \nARMOR: [ENEMY ARMOR]\n 
*/
void Tavern::printCombatQueue() {
    // Create a copy of the combat queue
    std::queue<Character*> temp = combat_queue_;

    // Iterate through the copy
    while (!temp.empty()) {
        Character* currentEnemy = temp.front();
        // Print details
        std::cout << "(ENEMY) " << currentEnemy->getName() << ": LEVEL " << currentEnemy->getLevel() << " " << currentEnemy->getRace() <<
            ". \nVITALITY: " << currentEnemy->getVitality() << " \nARMOR: " << currentEnemy->getArmor() << "\n";
        temp.pop();
    }
}
/** THE FOLLOWING FUNCTIONS WILL MANAGE THE COMBAT - YOU SHOULD CONSIDER HOW THESE WILL AFFECT THE CHARACTERS AND WHAT ADDITIONAL MEMBER FUNCTION YOU NEED TO IMPLEMENT IN THE CHARACTER CLASS TO SUPPORT THESE ACTIONS */



/** 
        @post : If there are no enemies in the combat queue, do nothing.
              : Otherwise do all of the following
              :     - The action queue must be emptied before the new actions are added.
              :     - Print out the start of turn and details of the target enemy in the form:
                      : YOUR TURN\n
                      : (ENEMY) [ENEMY NAME]: LEVEL [ENEMY LEVEL] [ENEMY RACE]. \nVITALITY: [ENEMY VITALITY] \nARMOR: [ENEMY ARMOR]\n\n 
    
              :     - Repeat the following process thrice (i.e. read three actions from input): 
              :           - Print the actions that are available to the main character, and read 
                            a non-negative number from input, corresponding to an action. 
                            Printing the available options should be of the following form. 
                            You may consider writing a helper function for this.
                            :Choose an action(1-4):\n1: BUFF_Heal\t\t2: BUFF_MendMetal\t\t3: ATT_Strike\t\t4: ATT_ThrowTomato\n
              :           - If the input is invalid (valid inputs will be 1,2,3, or 4 only.), 
                          keep prompting for a non-negative number that is within range, by
                          printing "Invalid input. Please enter a number between 1 and 4 inclusive.\n" and prompt for input again.
              :           - When a valid action is read, 
                          it is added to the main character's action queue.    
*/
void Tavern::actionSelection(){
  if(!combat_queue_.empty()){
    getMainCharacter()->clearActionQueue();
    if(getMainCharacter()->getActionQueue().empty()){
      std::cout << "YOUR TURN\n" << "(ENEMY) " << getTarget()->getName() << ": LEVEL " << getTarget()->getLevel() << " " << getTarget()->getRace()
      << ". \nVITALITY: " << getTarget()->getVitality() << " \nARMOR: " << getTarget()->getArmor() << "\n\n";
      actionHelper();
    }
  }

}
void Tavern::actionHelper(){
  int temp;
  bool dummy = false;
  int counter = 0;
  while(counter != 3){
    if(!dummy){
      std::cout << "Choose an action (1-4):\n" << "1: BUFF_Heal\t\t2: BUFF_MendMetal\t\t3: ATT_Strike\t\t4: ATT_ThrowTomato\n";
    }
    std::cin >> temp;
    if(temp > 0 && temp < 5){
      getMainCharacter()->addAction(temp - 1);
      counter++;
      dummy = false;
    }
    else{
      std::cout << "Invalid input. Please enter a number between 1 and 4 inclusive.\n";
      dummy = true;
    }
  }
}
/**
        @post : If there are no actions in the main character's action queue, 
                or there are no enemies in the combat queue, do nothing.
                
                Otherwise do all of the following:            
                
                1. If the Buff stack is not empty, apply the buff once and decrement the turns.
                   Any time a Buff's turns goes to zero, it is removed
                   from the stack. Print out the results of the action as described below.
                2. While there are actions on the action queue:
                - take the next action off the queue
                - if the next action is  a buff, apply once and push it onto the buff stack after 
                  decrementing the turns. 
                  BUFF_Heal lasts for 3 turns in total, while BUFF_MendMetal lasts
                  for 2 turns in total. Print out the results of the action as described below.
                - if the next action is an attack, execute it against the enemy at the front of
                  the combat queue. Print out the results of the action as described below. 
                 - if after this action there are no more enemies to fight, clear the action
                   queue and return.
                3. Print "END OF TURN\n" 
          
            : More details:
        
            : After applying each action, print out the results of the action as follows:
            : [MAINCHARACTER NAME] used [ACTION NAME]!
            : \n(YOU) [MAINCHARACTER NAME]: LEVEL [MAINCHARACTER LEVEL] [MAINCHARACTER RACE]. \nVITALITY: [MAINCHARACTER VITALITY] \nARMOR: [MAINCHARACTER ARMOR]\n
            : \n(ENEMY) [ENEMY NAME]: LEVEL [ENEMY LEVEL] [ENEMY RACE]. \nVITALITY: [ENEMY VITALITY] \nARMOR: [ENEMY ARMOR]\n 

             Where [ACTION NAME] is one of [Heal, MendMetal, Strike, ThrowTomato]
            
            :   Whenever an enemy's vitality becomes <=0 after an attack, also print out 
                "[CHARACTER NAME] DEFEATED\n" 
                and remove the enemy from the combat queue AND let them exit the tavern. 
                Then carry out the remaining actions, if any, against the next enemy on the
                combat queue.
          
*/

void Tavern::turnResolution() {
    if (combat_queue_.empty() || getMainCharacter()->getActionQueue().empty()) {
        return;
    }

    if (!getMainCharacter()->isBuffEmpty()) {
        if (!getMainCharacter()->getBuffStack().empty()) {
            if (getMainCharacter()->getBuffStack().top().name_ == "BUFF_Heal") {
                getMainCharacter()->heal();
                getMainCharacter()->getBuffStack().top().turns_--;
                if (getMainCharacter()->getBuffStack().top().turns_ == 0) {
                    getMainCharacter()->getBuffStack().pop();
                }
            } else if (getMainCharacter()->getBuffStack().top().name_ == "BUFF_MendMetal") {
                getMainCharacter()->mendMetal();
                getMainCharacter()->getBuffStack().top().turns_--;
                if (getMainCharacter()->getBuffStack().top().turns_ == 0) {
                    getMainCharacter()->getBuffStack().pop();
                }
            }
        }
    }//done

    // Part 2
    std::string storage = "";
    while (!getMainCharacter()->getActionQueue().empty()) {
        if (getMainCharacter()->getActionQueue().front() == 0) {
            getMainCharacter()->heal();
            getMainCharacter()->getBuffStack().push(Buff{"BUFF_Heal", 2});
            storage = "Heal";
        } else if (getMainCharacter()->getActionQueue().front() == 1) {
            getMainCharacter()->mendMetal();
            getMainCharacter()->getBuffStack().push(Buff{"BUFF_MendMetal", 1});
            storage = "MendMetal";
        } else if (getMainCharacter()->getActionQueue().front() == 2) {
            getMainCharacter()->strike(getTarget());
            storage = "Strike";
        } else if (getMainCharacter()->getActionQueue().front() == 3) {
            getMainCharacter()->throwTomato(getTarget());
            storage = "ThrowTomato";
        }
        getMainCharacter()->turnHelper();

        std::cout << "\n" << getMainCharacter()->getName() << " used " << storage << "!\n(YOU) " << getMainCharacter()->getName()
                  << ": LEVEL " << getMainCharacter()->getLevel() << " " << getMainCharacter()->getRace() << ".\nVITALITY: "
                  << getMainCharacter()->getVitality() << "\nARMOR: " << getMainCharacter()->getArmor() << "\n\n(ENEMY) "
                  << getTarget()->getName() << ": LEVEL " << getTarget()->getLevel() << " " << getTarget()->getRace()
                  << ".\nVITALITY: " << getTarget()->getVitality() << "\nARMOR: " << getTarget()->getArmor() << "\n";

    }

    if (!combat_queue_.empty()) {
        std::cout << "\nEND OF YOUR TURN\n\n";
    }
    if (getTarget()->getVitality() <= 0) {
        std::cout << getTarget()->getName() << " DEFEATED\n";
        combat_queue_.pop();
        exitTavern(getTarget());
    }
}


/**
        @param  : A pointer to the enemy
        @post   : Do all of the following:
                : 1. If the enemy's buff stack is not empty, apply buff once and decrement the
                  turns. Any time a Buff's turns_ goes to zero, it is removed
                  from the stack. Print out the results of the action as described below.
                : 2. Pick a random Action 
                    (one of BUFF_Heal, BUFF_MendMetal, ATT_Strike, ATT_ThrowTomato). 
                : If the selected action is a buff, apply once immediately and add it to the 
                  enemy's buff stack, performing the necessary turns update. 
                  Print out the results of the action as described below.
                : If the selected action is an attack, execute it against the main character.
                  Print out the results of the action as described below. 
                : More details:
                
                : After applying each action, print out the results of the action as follows:
                : [ENEMY NAME] used [ACTION NAME]!
                : \n(ENEMY) [ENEMY NAME]: LEVEL [ENEMY LEVEL] [ENEMY RACE]. \nVITALITY: [ENEMY VITALITY] \nARMOR: [ENEMY ARMOR]\n 
                : \n(YOU) [MAINCHARACTER NAME]: LEVEL [MAINCHARACTER LEVEL] [MAINCHARACTER RACE]. \nVITALITY: [MAINCHARACTER VITALITY] \nARMOR: [MAINCHARACTER ARMOR]\n
*/

void Tavern::enemyTurn(Character* mainChar) {
  if(!combat_queue_.empty()){
    if (!mainChar->isBuffEmpty()) {
        if (mainChar->getBuffStack().top().name_ == "BUFF_Heal") {
            mainChar->heal();
            mainChar->getBuffStack().top().turns_--;
            if (mainChar->getBuffStack().top().turns_ == 0) {
                mainChar->getBuffStack().pop();
            }
        } 
        else if (mainChar->getBuffStack().top().name_ == "BUFF_MendMetal") {
            mainChar->mendMetal();
            mainChar->getBuffStack().top().turns_--;
            if (mainChar->getBuffStack().top().turns_ == 0) {
                mainChar->getBuffStack().pop();
            }
        }
    }

    std::string storage = "";
    int randomNum = rand() % 4;
    if (randomNum == 0) {
      mainChar->heal();
      mainChar->getBuffStack().push(Buff{"BUFF_Heal", 2});
      storage = "Heal";
    } 
    else if (randomNum == 1) {
      mainChar->mendMetal();
      mainChar->getBuffStack().push(Buff{"BUFF_MendMetal", 1});
      storage = "MendMetal";
    } 
    else if (randomNum == 2) {
      mainChar->strike(getMainCharacter());
      storage = "Strike";
    } 
    else if (randomNum == 3) {
      mainChar->throwTomato(getMainCharacter());
      storage = "ThrowTomato";
    }
    std::cout << "ENEMY TURN\n";
    std::cout << mainChar->getName() << " used " << storage << "!";
    std::cout << "\n(ENEMY) " << mainChar->getName() << ": LEVEL "
    << mainChar->getLevel() << " "
    << mainChar->getRace() << "."
    << "\nVITALITY: " << mainChar->getVitality()
    << "\nARMOR: " << mainChar->getArmor() << "\n";

    std::cout << "\n(YOU) " << getMainCharacter()->getName() << ": "
    << "LEVEL " << getMainCharacter()->getLevel()
    << " " << getMainCharacter()->getRace() << "."
    << "\nVITALITY: " << getMainCharacter()->getVitality()
    << "\nARMOR: " << getMainCharacter()->getArmor() << "\n";
    }
  std::cout << "END OF ENEMY TURN\n";
}

/**
        @post : While the main character's vitality is > 0, and there are still enemies 
                  in the combat queue, do the following:
              :     - Call actionSelection()
                    - Call turnResolution()
                    - Call enemyTurn() with a pointer to the first enemy on combat queue.

              : If the main character's vitality has fallen to 0, print "YOU HAVE PERISHED."
              : If there are no more enemies in the combat queue, print "NO MORE ENEMIES."
*/
void Tavern::combat(){
  while(main_character_->getVitality() > 0 && !combat_queue_.empty()){
    actionSelection();
    turnResolution(); 
    enemyTurn(combat_queue_.front());
  }
  if (main_character_->getVitality() <= 0) {
    std::cout << "\nYOU HAVE PERISHED." << std::endl;
  }
  if (combat_queue_.empty()) {
    std::cout << "NO MORE ENEMIES." << std::endl;
  }
} 
