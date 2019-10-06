//
// Infix_Parser_Main.cpp
//  cs303Project1
//
//  Created by Coy Kwan, Brittney Maclennan, Ami Khalsa, and Collin Thomason on 10/3/19.
//  Copyright © 2019 Coy Kwan. All rights reserved.
//


#include <iostream>
#include "Infix_Parser.h"


using namespace std;

int main()
{
	Infix_Parser eval;
	cout << eval.eval("(2-1)*3");

	cout << endl << endl;

	cout << eval.eval("30-15");

	cout << endl << endl;

	cout << eval.eval("~10*5");

	cout << endl << endl;

	cout << eval.eval("5>3");

	cout << endl << endl;

	cout << eval.eval("--5*~4");

	cout << endl << endl;

	cout << eval.eval("++20+1");

	cout << endl << endl;

	cout << eval.eval("1 || 0");

	cout << endl << endl;

	cout << eval.eval("6>5 && 4>5");

	cout << endl << endl;

	cout << eval.eval("6 == 6");

	cout << endl << endl;

	return 0;
}


