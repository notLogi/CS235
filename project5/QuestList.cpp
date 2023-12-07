#include "QuestList.hpp"

/**
Default Constructor
*/
QuestList::QuestList() 
    : DoublyLinkedList<Quest*>() // no extra functions needed
{
}

/**
    @param: a reference to string name of an input file
    @pre: Formatting of the csv file is as follows:
        Title: A string
        Description: A string
        Completion Status: 0 (False) or 1 (True)
        Experience Points: A non negative integer
        Dependencies: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
        Subquests: A list of Quest titles of the form [QUEST1];[QUEST2], where each quest is separated by a semicolon. The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The dependencies and subquests are separated by a semicolon and may be NONE.
        - The dependencies and subquests may be in any order.
        - If any of the dependencies or subquests are not in the list, they should be created as new quests with the following information:
            - Title: The title of the quest
            - Description: "NOT DISCOVERED"
            - Completion Status: False
            - Experience Points: 0
            - Dependencies: An empty vector
            - Subquests: An empty vector
        - However, if you eventually encounter a quest that matches one of the "NOT DISCOVERED" quests while parsing the file, you should update all the quest details.
        Hint: update as needed using addQuest()
        

    @post: Each line of the input file corresponds to a quest to be added to the list. No duplicates are allowed.

*/
QuestList::QuestList(const std::string& input_file)
{
    std::ifstream file(input_file);
    if (file.fail()) {
      std::cerr << "File cannot be opened for reading." << std::endl;
      exit(1); // exit if failed to open the file
   }

    std::string junk, line, temp, title, description, completeddummy, experiencedummy, dependenciesdummy, subquestsdummy;

    getline(file, junk);

    while (getline(file, line)){
        std::vector<Quest*> dependencies, subquests;

        std::stringstream isString(line);
        getline(isString, title, ',');
        getline(isString, description, ',');
        getline(isString, completeddummy, ',');
        getline(isString, experiencedummy, ',');
        getline(isString, dependenciesdummy, ',');
        getline(isString, subquestsdummy);
        bool completed = std::stoi(completeddummy);//turns the string into bool
        int experience = std::stoi(experiencedummy);//turns the string into an integer.
        std::stringstream dependenciesInfo(dependenciesdummy);
        while (getline(dependenciesInfo, temp, ';')){//splits the string by ;: stringstream inside a stringstream
            if (temp != "NONE"){
                if (!contains(temp)){
                    Quest* depQuest = new Quest();
                    depQuest->title_ = temp;
                    depQuest->description_ = "NOT DISCOVERED";
                    addQuest(depQuest);
                    dependencies.push_back(depQuest);
                }
                else{
                    dependencies.push_back(getItem(getPosOf(temp)));
                }
            }
        }
        std::stringstream subquestsInfo(subquestsdummy);//same concept.
        while (getline(subquestsInfo, temp, ';')){
            if (temp != "NONE"){
                if (!contains(temp)){
                    Quest* subQuest = new Quest();
                    subQuest->title_ = temp;
                    subQuest->description_ = "NOT DISCOVERED";
                    addQuest(subQuest);
                    subquests.push_back(subQuest);
                }
                else{
                    subquests.push_back(getItem(getPosOf(temp)));
                }
            }
            
        }
        addQuest(title, description, completed, experience, dependencies, subquests);
    }

}

/**
    @param: A string reference to a quest title
    @return: The integer position of the given quest if it is in the QuestList, -1 if not found.
*/
int QuestList::getPosOf(const std::string& title) const {
    int position = 0;
    Node<Quest*>* current = getHeadNode();//gets the head node and loops until the last
    while(current != nullptr){
        if(current->getItem()->title_ == title){
            return position;
        }
        current = current->getNext();
        position++;
    }
    return -1;
}



/**
    @param: A string reference to a quest title
    @return: True if the quest with the given title is already in the QuestList
*/
bool QuestList::contains(const std::string& title) const
{
    return getPosOf(title) != -1;//this is the same concept with getposof so we can just return true if it != -1.
}



/**
    @pre: The given quest is not already in the QuestList
    @param:  A pointer to a Quest object
    @post:  Inserts the given quest pointer into the QuestList. Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
        
    @return: True if the quest was added or updated successfully, False otherwise
*/
bool QuestList::addQuest(Quest* questObject){
        if(contains(questObject->title_) && (getPointerTo(getPosOf(questObject->title_))->getItem())->description_ != "NOT DISCOVERED"){
            return false;
        }
        //these statements and conditions get the pointer of the object's title's position and points it to the item, sets it afterwards.
        else if(contains(questObject->title_) && (getPointerTo(getPosOf(questObject->title_))->getItem())->description_ == "NOT DISCOVERED"){
            getPointerTo(getPosOf(questObject->title_))->getItem()->description_ = questObject->description_;
            getPointerTo(getPosOf(questObject->title_))->getItem()->completed_ = questObject->completed_;
            getPointerTo(getPosOf(questObject->title_))->getItem()->experience_points_ = questObject->experience_points_;
            getPointerTo(getPosOf(questObject->title_))->getItem()->dependencies_ = questObject->dependencies_;
            getPointerTo(getPosOf(questObject->title_))->getItem()->subquests_ = questObject->subquests_;
            return true;
        } 
        else{
            if(insert(item_count_, questObject)){//inserts the questobject at the end.
                for(auto i : questObject->dependencies_){
                    if(!contains(i->title_)){
                        addQuest(i);
                    }
                }
                for(auto j : questObject->subquests_){
                    if(!contains(j->title_)){
                        addQuest(j);
                    }
                }
            }
            return true;
        }
        return false;
}



/**
    @param:  A reference to string representing the quest title
    @param:  A reference to string representing the quest description
    @param:  A reference to boolean representing if the quest is completed
    @param:  An reference to int representing experience points the quest rewards upon completion 
    @param:  A reference to vector of Quest pointers representing the quest's dependencies
    @param:  A reference to vector of Quest pointers representing the quest's subquests
    @post:   Creates a new Quest object and inserts a pointer to it into the QuestList. 
            If the quest is already in the list but is marked as "NOT DISCOVERED", update its details. (This happens when a quest has been added to the list through a dependency or subquest list)
            Each of its dependencies and subquests are also added to the QuestList IF not already in the list.
            

    @return: True if the quest was added or updated successfully, False otherwise

*/
bool QuestList::addQuest(const std::string& title, const std::string& description, const bool& completed, const int& experience, const std::vector<Quest*>& dependencies, const std::vector<Quest*>& subquests)
{
    Quest* quest = new Quest(title, description, completed, experience, dependencies, subquests);
    return addQuest(quest);
}

/**
    @param:  A Quest pointer
    @return: A boolean indicating if all the given quest's dependencies are completed
*/
bool QuestList::dependenciesComplete(Quest* quest) const
{
    for (auto d : quest->dependencies_)
    {
        if (d->completed_ == false)
        {
            return false;
        }
    }

    return true;
}


/**
    @param: A Quest pointer
    @return: A boolean if the given quest is available.
    Note: For a quest to be available, it must not be completed, and its dependencies must be complete.
*/
bool QuestList::questAvailable(Quest* questObject) const{
    if(questObject->completed_){
        return false;
    }
    for(int i = 0; i < questObject->dependencies_.size(); i++){
        if(!dependenciesComplete(questObject)){
            return false;
        }
    }
    return true;
}


/**
    @param: A Quest pointer
    @post: Prints the quest title and completion status
    The output should be of the form:
    [Quest Title]: [Complete / Not Complete]
    [Quest Description]\n\n
*/
void QuestList::printQuest(Quest* questObject) const{
    std::string dummy = " ";
    if(questObject->completed_){
        dummy = "Complete";
    }
    else if(!questObject->completed_){
        dummy = "Not Complete";
    }
    std::cout << questObject->title_ << ": " << dummy << std::endl;
    std::cout << questObject->description_ << "\n\n";
}
//helper function necessary for questquery
void QuestList::printDependencies(Quest* questObject){
    //if there is not dependencies or if the dependencies or all done, it will just print out the title and done.
    if (questObject->dependencies_.empty() || dependenciesComplete(questObject)){
        std::cout << "Ready: " << questObject->title_ << "\n";
        return;
    }
    //based loop where it goes through all the dependencies and if there are dependencies 
    //where if a dependency is not done, then it will do the recursion
    for (Quest* i : questObject->dependencies_){
        if (!i->completed_){
           printDependencies(i);
        }
    }

    std::cout << "  " << questObject->title_ << "\n";
}


/**
    @param: A string reference to a quest title
    @post:  Prints a list of quests that must to be completed before the given quest can be started (incomplete dependencies).
            If any of the quest's incomplete dependencies have an incomplete dependency, recursively print the quests that need to be done in order, indenting incomplete quests. 
            The indentation for incomplete quests is 2 spaces: "  "    
            The format of the list should be of the following forms for each different case:

            Query: [Quest Title]
            No such quest.
    
            Query: [Quest Title]
            Quest Complete
    
            Query: [Quest Title]
            Ready: [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            [Quest Title]
            
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
            [Quest Title]
    
            Query: [Quest Title]
            Ready: [Dependency0]
            Ready: [Dependency1]
            [Dependency2]
            [Quest Title]
            
    If the given quest title is not found in the list, print "No such quest."
*/
void QuestList::questQuery(const std::string& title)
{
    std::cout << "Query: " << title << "\n";
    if(contains(title)){
        if (getItem(getPosOf(title))->completed_){
            std::cout << "Quest Complete.\n";
        }

        else{
            printDependencies(getItem(getPosOf(title)));
            std::cout << "  ";
        }
    }
    else if(!contains(title)){
        std::cout << "No such quest.\n\n";
    }
}

/**
    @return: An integer sum of all the experience gained
    Note: This should only include experience from completed quests 
*/
int QuestList::calculateGainedExperience(){
    int totalExp = 0;

    for (int i = 0; i < item_count_; i++)
    {
        if (getItem(i)->completed_ == true)
        {
            totalExp += getItem(i)->experience_points_;
        }
    }

    return totalExp;
}

/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that can be gained from completing the main quest AND all its subquests.
    Note: Also consider the potential experience if a subquest itself has subquests.
*/
int QuestList::calculateProjectedExperience(Quest* questObject){
    int total = questObject->experience_points_;

    // Calculate the projected experience for subquests
    for (int i = 0; i <questObject->subquests_.size(); i++) {
        total += calculateProjectedExperience(questObject->subquests_[i]);
    }
    return total; 
}



/**
    @param: A quest pointer to a main quest
    @return: An integer sum of all the experience that has already been gained by completing the given quest's subquests.
    Note: Also consider the experience gained if a completed subquest itself has subquests.  
*/
int QuestList::calculatePathwayExperience(Quest* questObject){
    int total = 0;

    // Check if the main quest is completed
    if (questObject->completed_) {
        total += questObject->experience_points_;
    }

    // Check if there are subquests
    for (int i = 0; i < questObject->subquests_.size(); i++){
            // Check if the subquest is completed
        if (questObject->subquests_[i]->completed_){
                // Recursively calculate the subquest's subquests
            total += calculatePathwayExperience(questObject->subquests_[i]);
        }
    }
    return total;
}

/**
    @param: A string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every quest in the list.
        With filter "COMPLETE":   Only print out the completed quests in the list.
        With filter "INCOMPLETE": Only print out the incomplete quests in the list.
        With filter "AVAILABLE":  Only print out the available quests in the list.
        If an invalid filter is passed, print "Invalid Filter\n"
    Printing quests should be of the form:
    [Quest title]: [Complete / Not Complete]  
    [Quest description]\n
*/
void QuestList::questHistory(const std::string& filter) {
    if (filter == "NONE")
    {
        for (int i = 0; i < item_count_; i++){
            printQuest(getItem(i));
        }
    }

    else if (filter == "COMPLETE"){
        for (int i = 0; i < item_count_; i++){
            if (getItem(i)->completed_ == true){
                printQuest(getItem(i));
            }
        }
    }

    else if (filter == "INCOMPLETE"){
        for (int i = 0; i<item_count_; i++){
            if (getItem(i)->completed_ == false){
                printQuest(getItem(i));
            }
        }
    }

    else if (filter == "AVAILABLE"){
        for (int i = 0; i < item_count_; i++){
            if (questAvailable(getItem(i)) == true){
                printQuest(getItem(i));
            }
        }
    }

    else{
        std::cout << "Invalid Filter\n";
    }
}
//helper fucntion that is needed to do the recursion for printquestdetails.
void QuestList::printIndentedSubquests(Quest* questObject, int number){//helper function needed for printquestdetails
    for (int i = 0; i < number; i++){//it takes the number and indents it.
        std::cout << "  ";
    }
        //if the quest itself is (not) completed, it will print out the title and the completetion status.
    if (questObject->completed_ == false){
        std::cout << questObject->title_ << ": Not Complete\n";
    }
    else{
        std::cout << questObject->title_ << ": Complete\n";
    }
    // if it is not completed, for each individual subquest, if there's a subquest inside the subquest it will indent and will do the recursion.
    if (!questObject->completed_){
        for (int i = 0; i < questObject->subquests_.size(); i++){
            if (!questObject->subquests_[i]->completed_){
                printIndentedSubquests(questObject->subquests_[i], number +=1);
            }
            else{
                printIndentedSubquests(questObject->subquests_[i], number);
            }
        }
    }
}

/**
    @param: A quest pointer to a main quest
    @post:  Outputs subquest pathway. Print quest names with two spaces ("  ") of indentation for each subquest, recursively.
            Also print the percentage of experience gained in this pathway, rounded down to the lower integer.
            The format should be of the form:
            [Main Quest] ([Pathway XP] / [Projected XP]% Complete)
                [Subquest0]: [Complete / Not Complete]
                    [Sub-Subquest01]: [Complete / Not Complete]
                        [Sub-Subquest011]: [Complete / Not Complete]
                    [Subquest02]: [Complete / Not Complete]
            Hint: You can write a helper function to print the subquests recursively. If the given quest is already marked as completed, you can assume that all of its subquests are also completed.
*/
void QuestList::printQuestDetails(Quest* questObject)
{
    int projected = calculateProjectedExperience(questObject);
    int pathway = calculatePathwayExperience(questObject);
    int percent;
    if(projected != 0){
        percent = (pathway * 100 / projected);
    }
   

    std::cout << questObject->title_ << " (" << percent << "% Complete)\n";
    
    if (!questObject->completed_){
        for (int i = 0; i < questObject->subquests_.size(); i++){
            printIndentedSubquests(questObject->subquests_[i], 1);
        }
    }
}