//
//  abstract_column.hpp
//  data_frame
//
//  Created by Ishan Phadke on 11/26/23.
//

#ifndef abstract_column_hpp
#define abstract_column_hpp

#include <stdio.h>
#include <iostream>

using std::string;

class AbstractColumn {
public:
    AbstractColumn();
    AbstractColumn(string iName, int iSize);
    
    string getName(void) const;
    int getSize() const;
    
    void setSize(int newSize);
    void setName(const string& newName);
    virtual void setValue(int index, int value) = 0;
    virtual void setValue(int index, string value) = 0;
    virtual string getType(void) = 0;
    virtual string getFormattedValue(int rowIndex) const = 0;
    
    
    // function to allocate space for the data variable. Takes in one int arguement
    virtual void allocate(int num_of_rows);
    
    // hash function for the column
    int header_hash_function(void);
    
    
protected:
    string name;
    int size;
};

#endif /* abstract_column_hpp */
