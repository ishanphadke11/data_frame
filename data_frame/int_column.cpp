//
//  int_column.cpp
//  data_frame
//
//  Created by Ishan Phadke on 12/5/23.
//

#include "int_column.hpp"
#include <iostream>
#include "abstract_column.hpp"

using std::endl;

IntColumn::IntColumn()
{
    data = nullptr;
}

/*
IntColumn::IntColumn(int* iData, string iName, int iSize)
{
    data = iData;
    name = iName;
    size = iSize;
}*/

IntColumn::IntColumn(string iName)
{
    name = iName;
    data = nullptr;
    size = 0;
}


void IntColumn::allocate(int num_of_rows)
{
    data = new int[num_of_rows];
}

void IntColumn::setData(int* newData)
{
    data = newData;
    size = sizeof(*newData)/sizeof(int);
}

void IntColumn::setValue(int index, int value)
{
    data[index] = value;
    
    if (size < index)
    {
        size++;
    }
}

void IntColumn::setValue(int index, string value)
{
    return;
}

string IntColumn::getType(void)
{
    return "int";
}

string IntColumn::getFormattedValue(int rowIndex) const
{
    return std::to_string(data[rowIndex]);
}

int* IntColumn::getData(void)
{
    return data;
}

ostream& operator<<(ostream& out, IntColumn& rightOp)
{
    int i;
    
    int* array = (int*)rightOp.data;
    
    for (i = 0; i < rightOp.size; i++)
    {
        out << array[i] << endl;
    }
    
    return out;
}
