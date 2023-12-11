
#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#include "BinarySearchTree.hpp"
#include <iostream>
#include "Item.hpp"
#include <vector>
#include <string>
#include <algorithm>
class Inventory : public BinarySearchTree<Item*>{
public:
    Inventory();
    bool addItem(Item* object);
    Item* findItem(const std::string& name);
    Item* findItemHelper(BinaryNode<Item*>* root, const std::string& item);
    bool removeItem(const std::string& name);
    int getTotalGoldValue();
    int totalGoldHelper(std::shared_ptr<BinaryNode<Item*>> node);
    void printInventoryInOrder();
    void printInventoryInOrderHelper(std::shared_ptr<BinaryNode<Item*>> node);
    void vectorStorage(std::shared_ptr<BinaryNode<Item *>> node, std::vector<Item *> &items);
    void printInventory(bool ascendTrue, const std::string& criteria);
    void printDetails(Item* item);
};
#endif

