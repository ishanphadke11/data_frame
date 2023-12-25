//
//  string_column.cpp
//  data_frame
//
//  Created by Ishan Phadke on 12/5/23.
//

#include "string_column.hpp"

using std::endl;

StringColumn::StringColumn()
{
    data = nullptr;
}
StringColumn::StringColumn(string* iData)
{
    data = iData;
}

void StringColumn::allocate(int num_of_rows)
{
    data = new string[num_of_rows];
}

void StringColumn::setData(string* newData)
{
    data = newData;
    size = sizeof(*newData)/sizeof(string);
}

void StringColumn::setValue(int index, string value)
{
    data[index] = value;
    
    if (size < index)
    {
        size++;
    }
}

void StringColumn::setValue(int index, int value)
{
    return;
}

string StringColumn::getType(void)
{
    return "string";
}

string StringColumn::getFormattedValue(int rowIndex) const
{
    return data[rowIndex];
}

string* StringColumn::getData(void)
{
    return data;
}

ostream& operator<<(ostream& out, StringColumn& rightOp)
{
    int i;
    
    string* array = (string*)rightOp.data;
    
    for (i = 0; i < rightOp.size; i++)
    {
        out << array[i] << endl;
    }
    
    return out;
}
