//
//  abstract_column.cpp
//  data_frame
//
//  Created by Ishan Phadke on 11/26/23.
//

#include "abstract_column.hpp"
#include <iostream>

AbstractColumn::AbstractColumn()
{
    name = "unknown";
    size = 0;
}

AbstractColumn::AbstractColumn(string iName, int iSize)
{
    name = iName;
    size = iSize;
}

string AbstractColumn::getName(void) const
{
    return name;
}

int AbstractColumn::getSize() const
{
    return size;
}

int AbstractColumn::header_hash_function(void)
{
    const int capacity = 5;

    char firstLetter;
    if (name.empty()) {
        firstLetter = ' ';
    } else {
        firstLetter = name[0];
    }

    int hash = (firstLetter - 'a' + 1);

    
    hash = (hash % capacity + capacity) % capacity;

    return hash;
}

void AbstractColumn::setSize(int newSize)
{
    size = newSize;
}

void AbstractColumn::setName(const string& newName)
{
    name = newName;
}

void AbstractColumn::allocate(int num_of_rows)
{
    
}
