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
    inventory.findItem("Health Potion")->setTimePickedUp(200);
    inventory.findItem("Shield")->setTimePickedUp(300);
    // Find an item in the inventory
    Item* foundItem = inventory.findItem("Sword");

    // Display information about the found item
    if (foundItem != nullptr) {
        std::cout << "Found item: " << foundItem->getName() << " (Type: " << foundItem->getType() << ", Quantity: "
                  << foundItem->getQuantity() << ")" << std::endl;
    } else {
        std::cout << "Item not found in the inventory." << std::endl;
    }

    

    // Print the inventory in descending order based on gold value
    std::cout << "Inventory in Descending Order of Gold Value:" << std::endl;
    inventory.printInventory(false, "TIME");

    // Clean up memory (assuming proper destruction of the tree handles memory)
    delete sword;
    delete shield;
    delete potion1;
    delete potion2;

    return 0;
}

