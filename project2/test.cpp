
#include <iostream>
#include "Character.hpp"
#include "Mage.hpp"
#include "Scoundrel.hpp"
#include "Barbarian.hpp"
#include "Ranger.hpp"


int main(){
    Mage player5;//sets its name, race, school, weapon, and armor levels to default
    player5.setName("defaultMage");
    player5.setRace("ELF");
    player5.setVitality(5);
    player5.setArmor(3);
    player5.setLevel(2);
    player5.setEnemy();
    std::cout << "Name: " << player5.getName() << std::endl;
    std::cout << "Race: " << player5.getRace() << std::endl;
    std::cout << "Vitality: " << player5.getVitality() << std::endl;
    std::cout << "Armor: " << player5.getArmor() << std::endl;
    std::cout << "Level: " << player5.getLevel() << std::endl;
    std::cout << "School: " << player5.getSchool() << std::endl;
    std::cout << "Weapon: " << player5.getCastingWeapon() << std::endl;
    if(player5.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player5.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    Mage player("SPYNACH", "ELF", 6, 5, 4, false); //parameterized constructor for mage
    player.setSchool("Illusion");
    player.setCastingWeapon("wand");
    player.setIncarnateSummon(true);
    std::cout << "Name: " << player.getName() << std::endl;
    std::cout << "Race: " << player.getRace() << std::endl;
    std::cout << "Vitality: " << player.getVitality() << std::endl;
    std::cout << "Armor: " << player.getArmor() << std::endl;
    std::cout << "Level: " << player.getLevel() << std::endl;
    std::cout << "School: " << player.getSchool() << std::endl;
    std::cout << "Weapon: " << player.getCastingWeapon() << std::endl;
    if (player.hasIncarnateSummon() == false){
        std::cout << "Can't summon" << std::endl;
    }
    else if (player.hasIncarnateSummon() == true){
        std::cout << "Can summon" << std::endl;
    }
    if(player.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    Scoundrel player6;//default constructor for scoundrel
    player6.setName("defaultScoundrel");
    player6.setRace("HUMAN");
    player6.setVitality(6);
    player6.setArmor(4);
    player6.setLevel(3);
    player6.setEnemy();
    std::cout << "Name: " << player6.getName() << std::endl;
    std::cout << "Race: " << player6.getRace() << std::endl;
    std::cout << "Vitality: " << player6.getVitality() << std::endl;
    std::cout << "Armor: " << player6.getArmor() << std::endl;
    std::cout << "Level: " << player6.getLevel() << std::endl;
    if(player6.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player6.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    Scoundrel player2("FLEA", "DWARF", 12, 7, 5, false);//parameterized constructor for scoundrel
    player2.setDagger("Adamant");
    player2.setFaction("Cutpurse");
    player2.setDisguise(true);
    std::cout << "Name: " << player2.getName() << std::endl;
    std::cout << "Race: " << player2.getRace() << std::endl;
    std::cout << "Vitality: " << player2.getVitality() << std::endl;
    std::cout << "Armor: " << player2.getArmor() << std::endl;
    std::cout << "Level: " << player2.getLevel() << std::endl;
    std::cout << "Dagger: " << player2.getDagger() << std::endl;
    std::cout << "Faction: " << player2.getFaction() << std::endl;
    if (player2.hasDisguise() == false){
        std::cout << "No disguise" << std::endl;
    }
    else if(player2.hasDisguise() == true){
        std:: cout << "Has a disguise" << std::endl;
    }
    if(player2.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player2.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    Ranger player7;//default constructor for ranger
    player7.setName("defaultRanger");
    player7.setRace("UNDEAD");
    player7.setVitality(8);
    player7.setArmor(4);
    player7.setLevel(5);
    player7.setEnemy();
    std::cout << "Name: " << player7.getName() << std::endl;
    std::cout << "Race: " << player7.getRace() << std::endl;
    std::cout << "Vitality: " << player7.getVitality() << std::endl;
    std::cout << "Armor: " << player7.getArmor() << std::endl;
    std::cout << "Level: " << player7.getLevel() << std::endl;    
    if(player7.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player7.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }                               
    Ranger player4("MARROW", "UNDEAD", 9, 6, 5, true);//paramterized constructor for ranger
    player4.addArrows("Wood", 30);
    player4.addArrows("Fire", 5);
    player4.addArrows("Water", 5);
    player4.addArrows("Poison", 5);
    player4.addAffinity("Fire");
    player4.addAffinity("Poison");
    player4.setCompanion(true);
    std::cout << "Name: " << player4.getName() << std::endl;
    std::cout << "Race: " << player4.getRace() << std::endl;
    std::cout << "Vitality: " << player4.getVitality() << std::endl;
    std::cout << "Armor: " << player4.getArmor() << std::endl;
    std::cout << "Level: " << player4.getLevel() << std::endl;
    const std::vector<Arrows>& printarrows = player4.getArrows();
        for (int i = 0; i < printarrows.size(); i++) {
            std::cout << "Type: " << printarrows[i].type_ << ", Quantity: " << printarrows[i].quantity_ << std::endl;
    }
    const std::vector<std::string>& printaffinities = player4.getAffinities();
        for (int i = 0; i < printaffinities.size(); i++) {
            std::cout << printaffinities[i] << std::endl;
    }
    if(player4.getCompanion() == true){
        std::cout << "Yes" << std::endl;
    }
    else if(player4.getCompanion() == false){
        std::cout << "No" << std::endl;
    }
    if(player4.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player4.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    Barbarian player9;//default contructor for barbarian
    player9.setName("defaultBarbarian");
    player9.setRace("HUMAN");
    player9.setVitality(10);
    player9.setArmor(5);
    player9.setLevel(5);
    player9.setEnemy();
    std::cout << "Name: " << player9.getName() << std::endl;
    std::cout << "Race: " << player9.getRace() << std::endl;
    std::cout << "Vitality: " << player9.getVitality() << std::endl;
    std::cout << "Armor: " << player9.getArmor() << std::endl;
    std::cout << "Level: " << player9.getLevel() << std::endl;
    if(player9.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player9.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    Barbarian player3("BONK", "HUMAN", 11, 5, 5, true);//parameterized constructor for barbarian
    player3.setMainWeapon("MACE");
    player3.setSecondaryWeapon("ANOTHERMACE");
    player3.setEnrage(true);
    std::cout << "Name: " << player3.getName() << std::endl;
    std::cout << "Race: " << player3.getRace() << std::endl;
    std::cout << "Vitality: " << player3.getVitality() << std::endl;
    std::cout << "Armor: " << player3.getArmor() << std::endl;
    std::cout << "Level: " << player3.getLevel() << std::endl;
    if(player3.isEnemy() == true){
        std::cout << "Enemy: TRUE" << std::endl;
    }
    else if(player3.isEnemy() == false){
        std::cout << "Enemy: FALSE" << std::endl;
    }
    std::cout << "Main weapon: "<< player3.getMainWeapon() << std::endl;
    std::cout << "Secondary weapon: " << player3.getSecondaryWeapon() << std::endl;
    if(player3.getEnrage() == false){
        std::cout << "Enraged: FALSE" << std::endl;
    }
    else if(player3.getEnrage() == true){
        std::cout << "Enraged: TRUE" << std::endl;
    }
}