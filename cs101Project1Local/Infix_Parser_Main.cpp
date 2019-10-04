//
//  main.cpp
//  cs101Project1Local
//
//  Created by Coy Kwan on 10/3/19.
//  Copyright © 2019 Coy Kwan. All rights reserved.
//

#include <iostream>
#include "Infix_Parser.h"
using namespace std;

int main()
{
    Infix_Parser eval;
    cout << eval.eval("");
    cout << endl;
    return 0;
}

