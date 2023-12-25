//
//  main.cpp
//  data_frame
//
//  Created by Ishan Phadke on 11/12/23.
//

#include <iostream>
#include "data_frame.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    
    DataFrame* d1 = new DataFrame(argv[2]);
    DataFrame* d2 = d1->slice("First_Name");
    
    double* array = new double[4];
    int* a1 = new int[4];
    
    d1->display_data();
    
    d2->display_data();
 
    array = d1->average("Score", "Last_Name");
    
    for (int i = 0; i < 4; i++)
    {
        cout << array[i] << endl;
    }
    
    a1 = d1->sum("Score", "Last_Name");
    
    for (int i = 0; i < 4; i++)
    {
        cout << a1[i] << endl;
    }
    
    a1 = d1->max("Score", "Last_Name");
    
    for (int i = 0; i < 4; i++)
    {
        cout << a1[i] << endl;
    }
    
    a1 = d1->min("Score", "Last_Name");
    
    for (int i = 0; i < 4; i++)
    {
        cout << a1[i] << endl;
    }
    
    return 0;
}
