//
//  data_frame.hpp
//  data_frame
//
//  Created by Ishan Phadke on 11/12/23.
//

#ifndef data_frame_hpp
#define data_frame_hpp

#include <stdio.h>
#include <fstream>
#include "hash_table.hpp"
#include "column.hpp"
#include <vector>
#include "abstract_column.hpp"
#include <list>
#include <map>

using namespace std;

// DataFrame Class Definition. Includes an array of Columns called data, a string type variable to stare the header, int type variable to store the number of rows and columns, the file which is to be read and a HashTable variable called subject index which stores a hash table with the key being the subject. Private helper functions include functions to find number of columns and rows, function to load file, allocate data, read data, and read the header
class DataFrame {
public:
    
    // constructors
    DataFrame();
    DataFrame(AbstractColumn** iData, int numCols, int numRows);
    DataFrame(string fileName);
    DataFrame(unordered_map<string, list<int>> map, int* array);
    
    // function to display the data
    void display_data(void);
    
    // slice function returns a data frame with just one column of the header entered
    DataFrame* slice(string columnName);
    
    double* average(string columnName, string groupByColumnName = " ");
    int* sum(string columnName, string groupByColumnName = " ");
    int* max(string columnName, string groupByColumnName = " ");
    int* min(string columnName, string groupByColumnName = " ");
    
    // getter function returns the data
    AbstractColumn** getData(void) {return data;};

    AbstractColumn& operator[](int index);
    
private:
    AbstractColumn** data;
    string header;
    int num_of_columns;
    int num_of_rows;
    fstream file;
    int find_num_of_columns();
    int find_num_of_rows(string fileName);
    fstream load_file(string fileName);
    //void allocate_data(void);
    void read_data(string fileName);
    void read_header(string fileName);
    HashTable* subjectIndex;
};



#endif /* data_frame_hpp */
