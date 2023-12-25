//
//  column.hpp
//  data_frame
//
//  Created by Ishan Phadke on 11/18/23.
//

#ifndef column_hpp
#define column_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

// Column Class definition. Includes a T type array, int type size variable, and string type variable for the name of the column
class Column {
public:
    
    // Constructors
    Column();
    Column(int* iData, int iSize, string iName);
    
    // getter functions
    string getName(void) const;
    int getSize() const;
    int* getData() const;
    
    // setter functions
    void setData(int* newData);
    void setValue(int index, int value);
    void setSize(int newSize);
    void setName(const std::string& newName);
    
    // function to allocate space for the data variable. Takes in one int arguement
    void allocate(int num_of_rows);
    
    // hash function for the column
    int header_hash_function(void);
    
    // overloaded insertion operator as a friend function
    friend ostream& operator<<(ostream& out, Column& rightOp);
    
private:
    int* data;
    int size;
    string name;
};

#endif /* column_hpp */
