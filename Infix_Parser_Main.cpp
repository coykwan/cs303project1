#include "stdafx.h"
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


	system("pause");
	return 0;
}


