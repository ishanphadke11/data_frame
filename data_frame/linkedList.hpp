//
//  linkedList.hpp
//  data_frame
//
//  Created by Ishan Phadke on 11/17/23.
//

#ifndef linkedList_hpp
#define linkedList_hpp

#include <stdio.h>
#include "list_node.hpp"

using namespace std;

// linked list class has one private member of type ListNode*

class LinkedList {
public:
    
    // constructors
    LinkedList():head(nullptr){}
    LinkedList(ListNode *iHead):head(iHead){}
    
    
    // destructor
    ~LinkedList();
    
    // getter functions
    ListNode* getHead(void) const
    {
        return head;
    }
    
    // setter functions
    void setHead(ListNode* newHead) {
        head = newHead;
    }
    
    // fucntion to insert new node at the head
    void preAppend(void* newValue);
    

private:
    ListNode* head;
};


#endif /* linkedList_hpp */
