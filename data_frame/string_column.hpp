//
//  string_column.hpp
//  data_frame
//
//  Created by Ishan Phadke on 12/5/23.
//

#ifndef string_column_hpp
#define string_column_hpp

#include <stdio.h>
#include <iostream>
#include "abstract_column.hpp"

using std::ostream;

class StringColumn : public AbstractColumn {
public:
    
    StringColumn();
    StringColumn(string* iData);
    
    void setData(string* newData);
    void setValue(int index, int value) override;
    void setValue(int index, string value) override;
    string getType(void) override;
    string* getData(void);
    string getFormattedValue(int rowIndex) const override;
    
    void allocate(int num_of_rows) override;
    
    friend ostream& operator<<(ostream& out, StringColumn& rightOp);
    
private:
    string* data;
};

#endif /* string_column_hpp */
