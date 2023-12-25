//
//  data_frame.cpp
//  data_frame
//
//  Created by Ishan Phadke on 11/12/23.
//

#include "data_frame.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include "abstract_column.hpp"
#include "int_column.hpp"
#include "string_column.hpp"
#include "linkedList.hpp"
#include <map>
#include <list>


using namespace std;



// DataFrame Constructor has an argument of string type which is the file name. First it loads the given file. It finds the number of rows and columns and stores them in the respective variables. It allocates data based on the number of rows and columns. It then reads the data from the file and stores it in the data variable. It then splits the header into words and inserts them into the hash table
DataFrame::DataFrame(string fileName)
{
    file = load_file(fileName); // open file
    string word;
    num_of_columns = find_num_of_columns(); // find the number of columns in the file
    num_of_rows = find_num_of_rows(fileName); // find the number of rows in the file
    //allocate_data(); // allocate data based on the number of rows and columns
    read_data(fileName); // read data from the file
}

// DataFRame Constructor has a Column* argument. It assigns the data variable to the argument that is passed in to create a data frame with the newData column
DataFrame::DataFrame(AbstractColumn** iData, int numCols, int numRows)
{
    num_of_columns = numCols;
    num_of_rows = numRows;

    // Allocate space for data
    data = new AbstractColumn*[num_of_columns];

    // Copy the columns from the provided array to the DataFrame
    for (int i = 0; i < num_of_columns; ++i) {
        data[i] = iData[i];
    }

    // Build the subject index
    subjectIndex = new HashTable();

    // Populate the subject index with column names and corresponding pointers
    for (int n = 0; n < num_of_columns; ++n) {
        subjectIndex->put(data[n]->getName(), data[n]);
    }
}

DataFrame::DataFrame(unordered_map<string, list<int>> map, int* array)
{
    
}

// Private function that returns the number of columns that are in the file. Takes in no parameters and returns an int
int DataFrame::find_num_of_columns(void)
{
    int numColumns = 0;
    
    string header;
    string word;
    
    getline(file, header, '\n'); // read the header from the file
    
    stringstream ss(header); // turn string into sstream
    
    while (getline(ss, word, ',')) // get each individual word from the
    {
        numColumns++; // increment numColumns
    }
    
    return numColumns;
}

// Private function to find the number of rows. Takes in the fileName so it can open a temp file to read the whole file and count the number of rows. Returns an int
int DataFrame::find_num_of_rows(string fileName)
{
    string line;
    int num_of_rows = 0;
    fstream temp;
    
    temp.open(fileName); // open the same file but with a temporary variable
    
    getline(temp, line, '\n'); // get the header. header does not count as one of the rows
    
    while (!(temp.eof())) // go until the end of the file
    {
        getline(temp, line, '\n'); // read each line
        num_of_rows++; // increment num_of_rows
    }
    
    temp.close(); // clsoe file
    
    return num_of_rows;
}

// Private function opens the file by the fileName that is passed as an argument. Opens the file and returns an fstream type (a file)
fstream DataFrame::load_file(string fileName)
{
    fstream file;
    
    file.open(fileName); // open file
    
    if (file.fail()) // check if file opened succesfully
    {
        cout << "Error opening file" << endl;
        exit(1);
    }
    
    return file;
}

// Private function reads data from the given file. Takes in one argument which contains the name of the file that need to be opened. Does not return anything
void DataFrame::read_data(string fileName)
{
    fstream file;
    file.open(fileName); // Open the file to read the data
    
    // Read the header
    getline(file, header, '\n');
    
    stringstream headerStream(header);
    
    data = new AbstractColumn*[num_of_columns]; // allocate space for data as an array of AbstractColumn pointers
    
    for (int j = 0; j < num_of_columns; j++) 
    {
        string columnName;
        getline(headerStream, columnName, ','); // read the column name and data type
        
        // finds the position of '(' in the column name
        int openingParenthesisPos = static_cast<int>(columnName.find('('));
        
        // use the std::string substr function to create a substring of the column name
        string name = columnName.substr(0, openingParenthesisPos);
        
        // create another substring for the data type. Start at the position after '(' and end at the position before ')'.
        string dataType = columnName.substr(openingParenthesisPos + 1, columnName.size() - openingParenthesisPos - 2);
        
        if (dataType == "int") // if data type is an int create an IntColumn
        {
            data[j] = new IntColumn();
        } 
        
        else if (dataType == "string") // if data type is a string create a StringColumn
        {
            data[j] = new StringColumn();
        }
        
        data[j]->setName(name); // set name
        data[j]->allocate(num_of_rows);  // allocate space
    }
    
    // read and insert data from the file into the data frame
    for (int i = 0; i < num_of_rows; i++)
    {
        for (int j = 0; j < num_of_columns; j++) 
        {
            string value;
            
            if (j == num_of_columns - 1)
            {
                getline(file, value, '\n');
            }
            else
                getline(file, value, ','); // read value as a string
            
            // if current column's data type is int convert the string to an int and set the value
            if (data[j]->getType() == "int")            
            {
                int intValue = stoi(value);
                data[j]->setValue(i, intValue);
            } 
            
            // otherwise set it as a string
            else if (data[j]->getType() == "string")
            {
                data[j]->setValue(i, value);
            }
        }
    }
    
    subjectIndex = new HashTable(); // create a new instance of a Hash Table
    
    // put all columns into the hash table
    for (int n = 0; n < num_of_columns; n++)
    {
        subjectIndex->put(data[n]->getName(), data[n]);
    }
}

// Function displays the dataframe and prints it out as a table. Takes no arguments and returns nothing
void DataFrame::display_data() 
{
    for (int i = 0; i < num_of_rows; i++) 
    {
        for (int j = 0; j < num_of_columns; j++) 
        {
            cout << data[j]->getFormattedValue(i) << '\t';
        }
        cout << endl;
    }
}

// Slice function returns a DataFrame pointer with one Column. Has one argument of type string. The function finds the index of that subject using the hash table and then cretaes a column with that data. Then it creates a new DataFrame with just one column and returns it.
DataFrame* DataFrame::slice(string columnName)
{
    AbstractColumn* temp = (AbstractColumn*)subjectIndex->get(columnName);

    if (!temp) {
        cout << "Subject not found: " << columnName << endl;
        return nullptr;
    }

    int index = temp->header_hash_function();
    
    if (index == -1) {
        cout << "Subject not found: " << columnName << endl;
        return nullptr;
    }

    // Create a new AbstractColumn instance of the same type
    AbstractColumn* slicedColumn = nullptr;

    // Check the dynamic type of c and create a new column of the same type
    string columnType = temp->getType();
    
    if (columnType == "int") 
    {
        slicedColumn = new IntColumn();
        slicedColumn->allocate(num_of_rows);
        slicedColumn = (IntColumn*)subjectIndex->get(columnName);
    } 
    
    else if (columnType == "string") 
    {
        slicedColumn = new StringColumn();
        slicedColumn->allocate(num_of_rows);
        slicedColumn = (StringColumn*)subjectIndex->get(columnName);
    }

    // Set the name and size of the sliced column
    slicedColumn->setName(columnName);
    slicedColumn->setSize(num_of_rows);
   
    // Create a new DataFrame with the sliced column
    DataFrame* slice = new DataFrame(&slicedColumn, 1, num_of_rows);

    
    return slice;
}

double* DataFrame::average(string columnName, string groupByColumnName)
{
    double sum = 0.0;
    double average = 0.0;
    double* answer = new double[1];
    
    if (groupByColumnName == " ") {
        
        IntColumn* temp = (IntColumn*)subjectIndex->get(columnName);
        for (int j = 0; j < temp->getSize(); j++)
        {
            sum = sum + temp->getData()[j];
        }
                
        average = sum / temp->getSize();
        sum = 0;
        answer[0] = average;
        return answer;
    }

    // Create a map to store groups (key: unique values, value: list of values)
    unordered_map<string, list<int>> groups;

    // Get the column used for grouping
    AbstractColumn* groupByColumn = static_cast<StringColumn*>(subjectIndex->get(groupByColumnName));

    // Iterate through the rows and group values based on the groupByColumn
    for (int i = 0; i < num_of_rows; ++i) {
        // Get the value of the group by column for the current row
        string groupValue = groupByColumn->getFormattedValue(i);
            
        // Check if the group already exists in the map
        if (groups.find(groupValue) == groups.end()) {
            // If not, create a new list for this group
            groups[groupValue] = list<int>();
        }
        
        IntColumn* valueColumn = (IntColumn*)subjectIndex->get(columnName);
            
        int value = valueColumn->getData()[i];
        auto it = groups.find(groupValue);
        list<int> l1;
        groups[groupValue].push_back(value);
        
    }

    // Calculate average for each group
    int numGroups = groups.size();
    double* averages = new double[numGroups];
    int currentIndex = 0;
    
    for (const auto& entry : groups) {
        const list<int>& groupList = entry.second;
            
        // Calculate average for the current group
        double sum = 0.0;
        int count = 0;
        

        for (double value : groupList) {
            sum += value;
            count++;
        }

        averages[currentIndex] = sum / count;

        currentIndex++;
    }

    return averages;
}

int* DataFrame::sum(string columnName, string groupByColumnName)
{
    int* answer = new int[1];
    int sum = 0;
    
    if ((groupByColumnName == " "))
    {
        IntColumn* temp = (IntColumn*)subjectIndex->get(columnName);
        
        for (int j = 0; j < temp->getSize(); j++)
        {
            sum = sum + temp->getData()[j];
        }
            
        answer[0] = sum;
        sum = 0;
        
        return answer;
    }
    
    // Create a map to store groups (key: unique values, value: list of values)
    unordered_map<string, list<int>> groups;

    // Get the column used for grouping
    AbstractColumn* groupByColumn = static_cast<StringColumn*>(subjectIndex->get(groupByColumnName));

    // Iterate through the rows and group values based on the groupByColumn
    for (int i = 0; i < num_of_rows; ++i) {
        // Get the value of the group by column for the current row
        string groupValue = groupByColumn->getFormattedValue(i);
            
        // Check if the group already exists in the map
        if (groups.find(groupValue) == groups.end()) {
            // If not, create a new list for this group
            groups[groupValue] = list<int>();
        }
        
        IntColumn* valueColumn = (IntColumn*)subjectIndex->get(columnName);
            
        int value = valueColumn->getData()[i];
        auto it = groups.find(groupValue);
        list<int> l1;
        groups[groupValue].push_back(value);
        
    }

    // Calculate average for each group
    int numGroups = groups.size();
    int* sums = new int[numGroups];
    int currentIndex = 0;
    
    for (const auto& entry : groups) {
        const list<int>& groupList = entry.second;
            
        // Calculate average for the current group
        double sum = 0.0;
        int count = 0;
        

        for (double value : groupList) {
            sum += value;
            count++;
        }

        sums[currentIndex] = sum;

        currentIndex++;
    }

    return sums;
}

int* DataFrame::max(string columnName, string groupByColumnName)
{
    int* answer = new int[1];
    int max = -999999;
    
    if ((groupByColumnName == " "))
    {
        IntColumn* temp = (IntColumn*)subjectIndex->get(columnName);
            
        for (int j = 0; j < temp->getSize(); j++)
        {
            if (temp->getData()[j] > max)
            {
                max = temp->getData()[j];
            }
        }
            
        answer[0] = max;
        
        return answer;
    }
    
    
    // Create a map to store groups (key: unique values, value: list of values)
    unordered_map<string, list<int>> groups;

    // Get the column used for grouping
    AbstractColumn* groupByColumn = static_cast<StringColumn*>(subjectIndex->get(groupByColumnName));

    // Iterate through the rows and group values based on the groupByColumn
    for (int i = 0; i < num_of_rows; ++i) {
        // Get the value of the group by column for the current row
        string groupValue = groupByColumn->getFormattedValue(i);
            
        // Check if the group already exists in the map
        if (groups.find(groupValue) == groups.end()) {
            // If not, create a new list for this group
            groups[groupValue] = list<int>();
        }
        
        IntColumn* valueColumn = (IntColumn*)subjectIndex->get(columnName);
            
        int value = valueColumn->getData()[i];
        auto it = groups.find(groupValue);
        list<int> l1;
        groups[groupValue].push_back(value);
        
    }

    // Calculate average for each group
    int numGroups = groups.size();
    int* maxValues = new int[numGroups];
    int currentIndex = 0;
    
    for (const auto& entry : groups) {
        const list<int>& groupList = entry.second;
            
        // Calculate average for the current group
        max = -99999;
        int count = 0;
        

        for (int value : groupList) 
        {
            if (value > max) 
            {
                max = value;
            }
            count++;
        }

        maxValues[currentIndex] = max;

        currentIndex++;
    }

    return maxValues;
}

int* DataFrame::min(string columnName, string groupByColumnName)
{
    int* answer = new int[1];
    int min = 999999;
    
    if ((groupByColumnName == " "))
    {
        IntColumn* temp = (IntColumn*)subjectIndex->get(columnName);
        
        for (int j = 0; j < temp->getSize(); j++)
        {
            if (temp->getData()[j] < min)
            {
                min = temp->getData()[j];
            }
        }
            
        answer[0] = min;
        
        return answer;
    }
    
    // Create a map to store groups (key: unique values, value: list of values)
    unordered_map<string, list<int>> groups;

    // Get the column used for grouping
    AbstractColumn* groupByColumn = static_cast<StringColumn*>(subjectIndex->get(groupByColumnName));

    // Iterate through the rows and group values based on the groupByColumn
    for (int i = 0; i < num_of_rows; ++i) {
        // Get the value of the group by column for the current row
        string groupValue = groupByColumn->getFormattedValue(i);
            
        // Check if the group already exists in the map
        if (groups.find(groupValue) == groups.end()) {
            // If not, create a new list for this group
            groups[groupValue] = list<int>();
        }
        
        IntColumn* valueColumn = (IntColumn*)subjectIndex->get(columnName);
            
        int value = valueColumn->getData()[i];
        auto it = groups.find(groupValue);
        list<int> l1;
        groups[groupValue].push_back(value);
        
    }

    // Calculate average for each group
    int numGroups = groups.size();
    int* minValues = new int[numGroups];
    int currentIndex = 0;
    
    for (const auto& entry : groups) {
        const list<int>& groupList = entry.second;
            
        // Calculate average for the current group
        min = 999999;
        int count = 0;
        

        for (int value : groupList)
        {
            if (value < min)
            {
                min = value;
            }
            count++;
        }

        minValues[currentIndex] = min;

        currentIndex++;
    }

    return minValues;
   
}

AbstractColumn& DataFrame::operator[](int index)
{
    return *data[index];
}
