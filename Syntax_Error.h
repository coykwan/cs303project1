//
//  Syntax_Error.h
//  cs303Project1
//
//  Created by Coy Kwan, Brittney Maclennan, Ami Khalsa, and Collin Thomason on 10/3/19.//  Copyright © 2019 Coy Kwan. All rights reserved.
//

#ifndef SYNTAX_ERROR_H_
#define SYNTAX_ERROR_H_
#include <stdexcept>
#include <string>
#include <sstream>

class Syntax_Error : public std::invalid_argument {
public:
    Syntax_Error(std::string msg) : std::invalid_argument(msg) {}
};
#endif
