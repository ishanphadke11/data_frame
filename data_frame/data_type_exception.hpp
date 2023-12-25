//
//  data_type_exception.hpp
//  data_frame
//
//  Created by Ishan Phadke on 12/9/23.
//

#ifndef data_type_exception_hpp
#define data_type_exception_hpp

#include <stdio.h>
#include <iostream>
#include <exception>

using std::string;

class WrongDataType : public std::invalid_argument {
public:
    explicit WrongDataType(const string& arg):invalid_argument(arg), message(arg){};
    
private:
    string message;
    
};

#endif /* data_type_exception_hpp */
