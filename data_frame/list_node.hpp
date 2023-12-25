//
//  list_node.hpp
//  data_frame
//
//  Created by Ishan Phadke on 11/17/23.
//

#ifndef list_node_hpp
#define list_node_hpp

#include <stdio.h>
#include "column.hpp"

using namespace std;

// Class for nodes of the linked list.
class ListNode {
public:
    // constructors
    ListNode();
    ListNode(void* iValue):data(iValue), next(nullptr){}
    ListNode(void* iData, ListNode * iNext):data(iData), next(iNext){}
    ListNode(int iValue);
    
    // getter functions
    void* getData(void) {return data;}
    ListNode* getNext(void) const {return next;}
    
    // setter functions
    void setData(void* newValue) {data = newValue;}
    void setNext(ListNode* newValue) {next = newValue;}
    
private:
    void* data; // stores the data of type entry
    ListNode* next; // popints to the next node
};

#endif /* list_node_hpp */
