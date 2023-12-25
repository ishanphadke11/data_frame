//
//  int_column.hpp
//  data_frame
//
//  Created by Ishan Phadke on 12/5/23.
//

#ifndef int_column_hpp
#define int_column_hpp

#include <stdio.h>
#include "abstract_column.hpp"

using std::ostream;

class IntColumn : public AbstractColumn {
public:
    
    IntColumn();
    IntColumn(int* iData, string iName, int iSize):AbstractColumn(iName, iSize) {data = iData;};
    IntColumn(string iName);
    
    void setData(int* newData);
    void setValue(int index, int value) override;
    void setValue(int index, string value) override;
    string getType(void) override;
    int* getData(void);
    string getFormattedValue(int rowIndex) const override;
    
    void allocate(int num_of_rows) override;
    
    friend ostream& operator<<(ostream& out, IntColumn& rightOp);
    
private:
    int* data;
};

#endif /* int_column_hpp */
