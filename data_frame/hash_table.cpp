//
//  hash_table.cpp
//  hashing
//
//  Created by Ishan Phadke on 10/9/23.
//

#include "hash_table.hpp"
#include "list_node.hpp"
#include "int_column.hpp"
#include "abstract_column.hpp"

// constant variable for the capacity of our arrays
const int capacity = 100;

// hash table constructor definition
HashTable::HashTable()
{
    eList = new LinkedList[capacity]; // allocate space for an array of linked lists with size capacity
    
    collisionCount = new int[capacity]; // allocate space for a collision count array with size capacity
    
    for (int i = 0; i < capacity; i++) {
        eList[i] = LinkedList();
        collisionCount[i] = 0;
    }
}

// function to put given entry into the hash table
void HashTable::put(string name, AbstractColumn* c)
{
    AbstractColumn* temp = new IntColumn(name);
    int index = temp->header_hash_function(); // hand the hash code for the given entry

    if (eList[index].getHead() == nullptr) // if the linked list at that particular index is null
    {
        // make a new node with given entry and set it as the first node of the linked list
        eList[index].setHead(new ListNode(c));
    }
    
    else // if there is already a node at that particular index
    {
        eList[index].preAppend(c); // insert the new entry into the linked list
        collisionCount[index]++; // increment collision count at that particular index
    }

    // print name, what index it is inserted in and the collision count at that index
    cout << name << " inserted at index " << index << " (Collisions: " << getCollisionCount(index) << ")" << endl;
}

void HashTable::put(string name, void* value)
{
    char firstLetter;
    
    if (name.empty()) {
        firstLetter = ' ';
    } else {
        firstLetter = name[0];
    }

    int hash = (firstLetter - 'a' + 1);

    
    hash = (hash % capacity + capacity) % capacity;

    if (eList[hash].getHead() == nullptr) // if the linked list at that particular index is null
    {
        // make a new node with given entry and set it as the first node of the linked list
        eList[hash].setHead(new ListNode(value));
    }
    
    else // if there is already a node at that particular index
    {
        eList[hash].preAppend(value); // insert the new entry into the linked list
        collisionCount[hash]++; // increment collision count at that particular index
    }
    
}

void* HashTable::get(string name)
{
    // create a temporary Column object with the provided name and a score of 0
    AbstractColumn* searchColumn = new IntColumn(name);
    
    // calculate the index based on the hash function for the searchEntry
    int index = searchColumn->header_hash_function();
    
    // find the entry with the matching name in the appropriate bucket
    ListNode* currentNode = eList[index].getHead();

    while (currentNode != nullptr)
    {
        AbstractColumn* temp = (AbstractColumn*)currentNode->getData();
        // find the entry with the given name
        if (temp->getName() == name)
        {
            return currentNode->getData(); // return that entry
        }
        
        currentNode = currentNode->getNext(); // if not found move onto the next node
    }

    // if entry is not found, return a default object
    return nullptr;
}

// Function to get the collision count for a specific bucket (index)
int HashTable::getCollisionCount(int index) const
{
    return collisionCount[index];
}
