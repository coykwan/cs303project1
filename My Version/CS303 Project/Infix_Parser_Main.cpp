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

	cout << eval.eval("@10*5");

	cout << endl << endl;

	system("pause");
	return 0;
}


