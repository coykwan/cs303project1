#include <iostream>
#include "Infix_Parser.h"
using namespace std;

int main()
{
	Infix_Parser eval;
	cout << eval.eval("(2-1)*3");
	return 0;
}
