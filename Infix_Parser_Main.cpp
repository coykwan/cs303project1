//
// Infix_Parser_Main.cpp
//  cs303Project1
//
//  Created by Coy Kwan, Brittney Maclennan, Ami Khalsa, and Collin Thomason on 10/3/19.
//  Copyright © 2019 Coy Kwan. All rights reserved.
//


#include "stdafx.h"
#include <iostream>
#include "Infix_Parser.h"


using namespace std;

int main()
{
	Infix_Parser eval;

	cout << eval.eval("1+2*3");

	cout << endl << endl;

	cout << eval.eval("2+2^2*3");

	cout << endl << endl;

	cout << eval.eval("1==2");

	cout << endl << endl;

	cout << eval.eval("1+3 > 2");

	cout << endl << endl;

	cout << eval.eval("(4>=4) && 0");

	cout << endl << endl;

	cout << eval.eval("(1+2)*3");

	cout << endl << endl;

	cout << eval.eval("++++2-5 * (3 ^ 2)");

	cout << endl << endl;

	cout << eval.eval("~10*~5");

	cout << endl << endl;

	system("pause");
	return 0;
	
}