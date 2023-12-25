#ifndef hash_table_hpp
#define hash_table_hpp

#include <stdio.h>
#include "linkedList.hpp"
#include "abstract_column.hpp"


// HashTable class definition. One private member of type Entry, one of type int* to track collisions

class HashTable {
public:
    // default constructor
    HashTable();
    
    // function to put an entry into the array
    void put(string name, AbstractColumn* c);
    
    void put(string name, void* value);
    
    // function to get the score of a given name
    void* get(string name);

    // function to get the collision count at a particular index
    int getCollisionCount(int index) const;
    
    LinkedList* getEList(void) const {return eList;};

private:
    LinkedList* eList;
    int* collisionCount;
};

#endif /*hash_table_hpp*/
