#include <iostream>
#include "Inventory.hpp"
int main() {
Inventory inventory;

    // Create some items
    Item* sword = new Item("Sword", WEAPON, 3, 50, 1);
    Item* shield = new Item("Shield", ARMOR, 2, 30, 1);
    Item* potion1 = new Item("Health Potion", CONSUMABLE, 1, 10, 3);
    Item* potion2 = new Item("Health Potion", CONSUMABLE, 1, 10, 2);

    // Add items to the inventory
    inventory.addItem(sword);
    inventory.addItem(shield);
    inventory.addItem(potion1);

    // Try adding another instance of the same consumable item
    inventory.addItem(potion2);


    

    // Print the inventory in descending order based on gold value
    std::cout << "Inventory in Descending Order of Gold Value:" << std::endl;
    inventory.printInventory(true, "TIME");
    std::cout << "time:" << inventory.findItem("Shield")->getTimePickedUp()<< std::endl;
    std::cout << "time:" << inventory.findItem("Health Potion")->getTimePickedUp()<< std::endl;
    std::cout << "time:" << inventory.findItem("Sword")->getTimePickedUp()<< std::endl;

    // Clean up memory (assuming proper destruction of the tree handles memory)
    delete sword;
    delete shield;
    delete potion1;
    delete potion2;

    return 0;
}

