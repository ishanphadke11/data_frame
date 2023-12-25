//
//  linked_list.cpp
//  hashing
//
//  Created by Ishan Phadke on 10/15/23.
//

#include "linkedList.hpp"
#include "list_node.hpp"

using namespace std;

// destructor for linked list

LinkedList::~LinkedList()
{
    ListNode* orgTemp = head;
    
    while (orgTemp != nullptr) {
        head = head->getNext();
        orgTemp->setNext(nullptr);
        delete orgTemp;
        orgTemp = head;
    }
}


// fucntion to insert a new node at the head of a linked list
void LinkedList::preAppend(void* newValue) 
{
    ListNode *newNode = new ListNode(newValue, head);
    head = newNode;
}
