#ifndef TAVERN_HPP
#define TAVERN_HPP
#include <iostream>
#include "Character.hpp"
#include "ArrayBag.hpp"
#include <cmath>
#include <string>

class Tavern : public ArrayBag<Character>{
public:
    Tavern();
    bool enterTavern(const Character& character);
    bool exitTavern(const Character& character);
    int getLevelSum() const;
    int calculateAvgLevel() const;
    int getEnemyCount() const;
    double calculateEnemyPercentage() const;
    int tallyRace(const std::string& race);
    void tavernReport();
private:
    int total_level_;//integer of the total level
    int total_enemies_;//stores the total number of enemies in an integer.
};
#endif