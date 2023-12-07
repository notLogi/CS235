#include <iostream>
#include "character.hpp"

int main(){
    Character player("Alice", "HUMAN", 100, 5, 5, false);
    player.setName("12312");
    player.setVitality(3);
    player.setArmor(10);
    player.setEnemy();
    std::cout << "Name: " << player.getName() << std::endl;
    std::cout << "Race: " << player.getRace() << std::endl;
    std::cout << "Vitality: " << player.getVitality() << std::endl;
    std::cout << "Armor: " << player.getArmor() << std::endl;
    std::cout << "Level: " << player.getLevel() << std::endl;
    if (player.isEnemy() == false){
        std::cout << "Enemy or not? " << "No"<< std::endl;
    }
    else if(player.isEnemy() == true){
        std::cout << "Enemy or not? " << "Yes"<< std::endl;
    }
    
}
