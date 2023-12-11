#include "Inventory.hpp"

Inventory::Inventory(){}//default constructor
/**
 * @param : A Pointer to the Item object to be added to the inventory.
 * @post  : The Item is added to the inventory, preserving the BST structure. The BST property is based on (ascending) alphabetical order of the item's name.
 *          If the item is type UNKNOWN, WEAPON, or ARMOR and is already in the inventory, it is not added.
      However, if another instance of an Item of type CONSUMABLE is being added (an item with the same name), its quantity is updated to the sum of the quantities of the two objects, and the time_picked_up_ variable is updated to that of the latest instance of the item being added.
 * @return true if the item was added to the inventory or updated, false otherwise.
 */
bool Inventory::addItem(Item* stuff){
    if(contains(stuff)){
        if(stuff->getType() == "CONSUMABLE"){
            getPointerTo(stuff)->getItem()->setQuantity(getPointerTo(stuff)->getItem()->getQuantity() + stuff->getQuantity());
            getPointerTo(stuff)->getItem()->updateTimePickedUp();
            return true;    
        }
        else{
            return false;
        }
    }
    add(stuff);
    getPointerTo(stuff)->getItem()->updateTimePickedUp();
    return true;
}
/**
 * @param   : A reference to string name of the item to be found.
 * @return  : An Item pointer to the found item, or nullptr if the item is not in the inventory.
 */
Item* Inventory::findItem(const std::string& name) {
    // Call the helper function with the root of the tree and the name to find
    Item* stuff = new Item;
    stuff->setName(name);
    if(contains(stuff)){
        return getPointerTo(stuff)->getItem();
    }
    else if(!contains(stuff)){
        delete stuff;
        return nullptr;
    }

}


/**
 * @param   : A reference to string name of the item to be removed from the inventory.
 * @return  : True if the item was found and removed or updated successfully, false otherwise.
 * @post    : If the item is found in the inventory, it is removed while preserving the BST structure.
              If a CONSUMABLE is removed, its quantity is decremented by one, but its time_picked_up_ remains the same. However, if it is the last item (it's quantity is 1 and is being removed), the item should be removed. Non-CONSUMABLE items should always be removed when they are found.
 */
bool Inventory::removeItem(const std::string& name){
    Item* stuff = new Item;
    stuff->setName(name);
    if(contains(stuff)){
        if(getPointerTo(stuff)->getItem()->getType() == "CONSUMABLE"){
            if(getPointerTo(stuff)->getItem()->setQuantity(getPointerTo(stuff)->getItem()->getQuantity() - 1) == 0){
                remove(stuff);
            }
            else{
                getPointerTo(stuff)->getItem()->setQuantity(getPointerTo(stuff)->getItem()->getQuantity() - 1);
            }

        }
        else{
            remove(stuff);
        }
        return true;
    }
    delete stuff;
    return false;
}
/**
 * @return    : The total sum of gold values of all items in the inventory.
                Note: consumable items may have quantity >1 and gold value must be
                      added for each item
 */ 
int Inventory::getTotalGoldValue(){
    return totalGoldHelper(getRoot());
}

int Inventory::totalGoldHelper(std::shared_ptr<BinaryNode<Item*>> node){
    if(node == nullptr){
        return 0;
    }
    int total = 0;
    if(node->getItem()->getType() == "CONSUMABLE"){
        total = node->getItem()->getQuantity() * node->getItem()->getGoldValue();
    }
    else{
        total = node->getItem()->getGoldValue();
    }
    return total + (totalGoldHelper(node->getLeftChildPtr())) + (totalGoldHelper(node->getRightChildPtr()));

}

/**
 * @post    : The names of all items in the Inventory are printed in ascending order.
 *            This function performs an in-order traversal of the binary search tree and prints the details of each item in the following format. 
        NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS.

 *            [NAME] ([TYPE])
              Level: [LEVEL]
              Value: [VALUE]
              Quantity: [QUANTITY]
   
              Example:
              TIRED GAUNTLETS (ARMOR)
              Level: 3
              Value: 25
        
              SMALL HEALTH POTION (CONSUMABLE)
              Level: 1
              Value: 10
              Quantity: 2
 * 
 */
void Inventory::printInventoryInOrder(){
    printInventoryInOrderHelper(getRoot());
}
// HELPER FUNCTION
void Inventory::printInventoryInOrderHelper(std::shared_ptr<BinaryNode<Item *>> node){
    if (node == nullptr){
        return;
    }

    printInventoryInOrderHelper(node->getLeftChildPtr());

    std::cout << node->getItem()->getName() << " "<< "(" << node->getItem()->getType() << ")"<< "\n";
    std::cout << "Level: " << node->getItem()->getLevel() << "\n";
    std::cout << "Value: " << node->getItem()->getGoldValue() << "\n";
    if (node->getItem()->getType() == "CONSUMABLE"){
        std::cout << "Quantity: " << node->getItem()->getQuantity() << "\n";
    }
    std::cout << "\n";

    printInventoryInOrderHelper(node->getRightChildPtr());
}

/**
 * @param   : a reference to bool if the items are to be printed in ascending order. 
 * @param   : a reference to string attribute which defines the order by which the items are to be printed. You may assume that the given parameter will be in one of the following forms: ["NAME"/"TYPE"/"LEVEL"/"VALUE"/"TIME"]
 * @post    : All items in the Inventory are printed in the order specified by the parameter.
 *          Example usage: inventory.printInventory(false, "LEVEL");
            NOTE: QUANTITY ONLY NEEDS TO BE DISPLAYED FOR CONSUMABLE ITEMS:
            TYPE, LEVEL, VALUE, TIME
            FEATHER DUSTER (WEAPON)
            Level: 5
            Value: 100

            TIRED GAUNTLETS (ARMOR)
            Level: 3
            Value: 50

            SMALL HEALTH POTION (CONSUMABLE)
            Level: 1
            Value: 10
            Quantity: 2

            NOODLES (CONSUMABLE)
            Level: 0
            Value: 120
            Quantity: 5
            TYPE, LEVEL, VALUE, TIME
 */
void Inventory::printInventory(bool ascendTrue, const std::string& criteria){
    std::vector<Item*> stuff;
    vectorStorage(getRoot(), stuff);
    if(criteria == "NAME"){
        std::sort(stuff.begin(), stuff.end(), [](Item* lhs, Item* rhs){
            return lhs->getName() < rhs->getName();
        });
    }
    else if(criteria == "TYPE"){
        std::sort(stuff.begin(), stuff.end(), [](Item* lhs, Item* rhs){
            return lhs->getType() < rhs->getType();
        });
    }
    else if(criteria == "LEVEL"){
        std::sort(stuff.begin(), stuff.end(), [](Item* lhs, Item* rhs){
            return lhs->getLevel() < rhs->getLevel();
        });
    }
    else if(criteria == "VALUE"){
        std::sort(stuff.begin(), stuff.end(), [](Item* lhs, Item* rhs){
            return lhs->getGoldValue() < rhs->getGoldValue();
        });
    }
    else if(criteria == "TIME"){
        std::sort(stuff.begin(), stuff.end(), [this](Item* lhs, Item* rhs){
            return lhs->getTimePickedUp() < rhs->getTimePickedUp();
        });
    }
    if(ascendTrue){
        for(int i = 0; i < stuff.size(); i++){
            printDetails(stuff[i]);
        }
    }
    else{
        for(int i = stuff.size() - 1; i >= 0; i--){
            printDetails(stuff[i]);
        }
    }
}
void Inventory::vectorStorage(std::shared_ptr<BinaryNode<Item*>> node, std::vector<Item *> &items){
    if (node != nullptr){
        vectorStorage(node->getLeftChildPtr(), items);
        items.push_back(node->getItem());
        vectorStorage(node->getRightChildPtr(), items);
    }
}
void Inventory::printDetails(Item* item){
    std::cout << item->getName() << " (" << item->getType() << ")\nLevel: " << item->getLevel() << "\nValue: " << item->getGoldValue() << "\n";
    if(item->getType() == "CONSUMABLE"){
        std::cout << "Quantity: " << item->getQuantity() << std::endl;
    }
    std::cout << std::endl;
}