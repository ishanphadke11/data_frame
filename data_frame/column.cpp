//
//  column.cpp
//  data_frame
//
//  Created by Ishan Phadke on 11/18/23.
//

#include "column.hpp"
#include <iostream>

using namespace std;

// Column class function which allocates space for the data. One int type argument which has the number of rows in the file. That will be the capacity of data


Column::Column()
{
    data = nullptr;
    size = 0;
    name = "unknown";
}


Column::Column(int* iData, int iSize, string iName)
{
    data = iData;
    size = iSize;
    name = iName;
}

string Column::getName(void) const
{
    return name;
}

int Column::getSize() const
{
    return size;
}

int* Column::getData() const
{
    return data;
}

void Column::setSize(int newSize)
{
    size = newSize;
}

void Column::setName(const std::string& newName)
{
    name = newName;
}

void Column::allocate(int num_of_rows)
{
    data = new int[num_of_rows];
}

void Column::setValue(int index, int value)
{
    data[index] = value;
    
    if (size < index)
    {
        size++;
    }
}

void Column::setData(int* newData)
{
    data = newData;
    size = sizeof(*newData)/sizeof(int);
}

int Column::header_hash_function(void)
{
    const int capacity = 5;  // Your specified capacity

    char firstLetter;
    if (name.empty()) {
        firstLetter = ' ';
    } else {
        firstLetter = name[0];
    }

    // Use the ASCII value of the first letter as the hash code
    int hash = (firstLetter - 'a' + 1);

    // Ensure the hash code is within the range [0, 4] (for capacity = 5)
    hash = (hash % capacity + capacity) % capacity;

    return hash;
}
// Overloaded insertion operator. Prints out the data of the column

ostream& operator<<(ostream& out, Column& rightOp)
{
    int i;
    
    int* array = (int*)rightOp.data;
    
    for (i = 0; i < rightOp.size; i++)
    {
        out << array[i] << endl;
    }
    
    return out;
}
