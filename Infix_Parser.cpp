//  Infix_Parser.cpp
//  cs303Project1
//
//  Created by Coy Kwan, Brittney Maclennan, Ami Khalsa, and Collin Thomason on 10/3/19.
//  Copyright Â© 2019 Coy Kwan. All rights reserved.
//


/** Implementation of Infix_To_Postfix that processes parentheses.*/


#include "stdafx.h"
#include "Infix_Parser.h"
#include <sstream>
#include <cctype>
#include <iostream>
#include <cmath>
using std::string;
using std::istringstream;
using std::isdigit;

using namespace std;

const string Infix_Parser::OPERATORS = "+-~*/%()[]{}^<>|&=?!$";
//? represents increment/decrement operators
//$ represents comparison operators
const int Infix_Parser::PRECEDENCE[] = { 5, 5, 8, 6, 6, 6, -1, -1, -1, -1, -1, -1, 7, 4, 4, 1, 2, 3, 8, 8, 4 };

//*******************************************************************
// A function to check if the expression meets infix syntax-p0
// if it does not, an appropriate exception will be thrown
// if it does, true is returned.
//******************************************************************


bool Infix_Parser::is_infix(const std::string& expression)
{
	//Checks if the expression starts with a binary operator.
	if (expression.at(0) == '+'
		|| expression.at(0) == '-'
		|| expression.at(0) == '/'
		|| expression.at(0) == '*'
		|| expression.at(0) == '^'
		|| expression.at(0) == '%'
		|| expression.at(0) == '<'
		|| expression.at(0) == '>'
		|| (expression.at(0) == '|' && expression.at(1) == '|')
		|| (expression.at(0) == '&' && expression.at(1) == '&')
		|| (expression.at(0) == '=' && expression.at(1) == '='))
	{
		if (expression.at(0) != expression.at(1))
		{
			throw Syntax_Error("Expression cannot start with a binary operator @ char 0");
		}
		else if (expression.at(0) == '|' || expression.at(0) == '&' || expression.at(0) == '=')
		{
			throw Syntax_Error("Expression cannot start with a binary operator @ char 0");
		}
	}

	//Checks to see if there are double binary operators or a unary operator followed by a binary operator
	for (long long unsigned int i = 1; i < expression.size(); i++)
	{
		if (is_operator(expression.at(i - 1)) && is_operator(expression.at(i)))
		{
			if (expression.at(i - 1) != '('
				&& expression.at(i - 1) != '{'
				&& expression.at(i - 1) != '['
				&& expression.at(i - 1) != ')'
				&& expression.at(i - 1) != '}'
				&& expression.at(i - 1) != ']')
			{
				if (((expression.at(i - 1) == expression.at(i))
					&& (expression.at(i - 1) == '-'
						|| (expression.at(i - 1) == '+')
						|| (expression.at(i - 1) == '~')
						|| (expression.at(i - 1) == '|')
						|| (expression.at(i - 1) == '&')
						|| (expression.at(i - 1) == '=')))
					|| ((expression.at(i - 1) == '<'
						|| expression.at(i - 1) == '>')
						&& expression.at(i) == '='))
				{
					break;
				}
				else if ((expression.at(i - 1) == '~' && expression.at(i) != '~')
					&& expression.at(i) != '('
					&& expression.at(i) != '{'
					&& expression.at(i) != '[')
				{
					throw Syntax_Error("A unary operator cannot be followed by a binary operator @ char "
						+ std::to_string(i));
				}
				else
				{
					if (expression.at(i) != '('
						&& expression.at(i) != '{'
						&& expression.at(i) != '['
						&& expression.at(i) != ')')
						throw Syntax_Error("Two binary operators in a row @ char "
							+ std::to_string(i));
				}
			}
		}
		
		// If an expression starts with an opening paranthese, allow it.
		else if (expression.at(0) == '(')
		{
			return true;
		}

		// If there is a negative number in the expression, allow it.
		else if (is_operator(expression.at(i - 1)) && isdigit(expression.at(i)))
		{
			return true;
		}

		// If the operation starts with a number, allow it.
		else if (isdigit(expression.at(i - 1)))
		{
			int value;
			char next;
			istringstream tokens(expression);
			tokens >> value;
			tokens >> next;
			if (isdigit(next))
			{
				string find = " ";
				find.push_back(next);
				throw Syntax_Error("Two operands in a row @ char "
					+ std::to_string(expression.find(find)));
				//returns the index of the space before the 2nd operand
			}
		}
	}

	return true;
}




/** Evaluates the current operator.
This function pops the two operands off the operand
stack and applies the operator.
@param op A character representing the operator
@throws Syntax_Error if top is attempted on an empty stack
*/

void Infix_Parser::eval_op(char op)
{
	if (this->operand_stack.empty())
		throw Syntax_Error("Operand stack is empty.");

	int rhs = this->operand_stack.top();

	this->operand_stack.pop();
	int result = 0;

	if (op == '?' || op == '$')
	{
		operator_stack.pop();
		switch (operator_stack.top())
		{
		case '+':
			result = rhs + 1;
			break;
		case '-':
			result = rhs - 1;
			break;
		default:
			op = operator_stack.top();

			if (this->operand_stack.empty())
				throw Syntax_Error("Operand stack is empty.");

			int lhs = this->operand_stack.top();
			this->operand_stack.pop();

			switch (op)
			{
			case '|':
				result = lhs || rhs;
				break;
			case '&':
				result = (lhs && rhs);
				break;
			case '=':
				result = (lhs == rhs);
				break;
			case '<':
				result = lhs <= rhs;
				break;
			case '>':
				result = lhs >= rhs;
			}
			break;
		}
	}
	else if (op == '~')
	{
		result = -rhs;
	}
	else if (op == '!')
	{
		result = !rhs;
	}
	else
	{
		if (this->operand_stack.empty())
			throw Syntax_Error("Operand stack is empty.REALLY??");

		int lhs = this->operand_stack.top();
		this->operand_stack.pop();

		switch (op)
		{
		case '+':
			result = lhs + rhs;
			break;
		case '-':
			result = lhs - rhs;
			break;
		case '*':
			result = lhs * rhs;
			break;
		case '/':
			result = lhs / rhs;
			break;
		case '%':
			result = lhs % rhs;
			break;
		case '^':
			result = pow(lhs, rhs);
			break;
		case '<':
			result = lhs < rhs;
			break;
		case '>':
			result = lhs > rhs;
			break;

		}
		//************************************************************************
		//NEED TO ADD OTHER OPERATORS HERE!!!!
		//************************************************************************
	}
	operand_stack.push(result);
}



int Infix_Parser::eval(const std::string& expression)
{
	is_infix(expression); //checks if the expression is infix. if it isn't, an exception will be thrown.

						  // Be sure both stacks are empty
	while (!operand_stack.empty())
		operand_stack.pop();

	while (!operator_stack.empty())
		operator_stack.pop();

	// Process each token
	istringstream tokens(expression);
	char next_token;
	while (tokens >> next_token)
	{
		char repeated_operator;
		if (isdigit(next_token))
		{

			tokens.putback(next_token);
			int value;

			tokens >> value;
			this->operand_stack.push(value);
		}
		else if (is_operator(next_token))
		{
			tokens >> repeated_operator;

			//If the next character is a repeated operator, process the first and then process '?'
			if (is_operator(repeated_operator) && repeated_operator == next_token)
			{
				// As long as there is a repeated operataor already on the stack, continue.
				if (!operator_stack.empty()) 
				{
				
					// If that repeated operator is for an increment or a decrement, continue.
					if (operator_stack.top() == '?')
					{
						// This will allow ++++ to function and increase the number by the appropriate amount.
						if (repeated_operator == '+')
						{
							tokens.putback(next_token);
							int value;

							tokens >> value;
							value = value + 1;
							this->operand_stack.push(value);
						}
						
					}
					
					
				}
					
				else {

					process_operator(next_token);
					operator_stack.push('?');
				}
			}

			else if (is_operator(repeated_operator) && repeated_operator == '=')
			{
				process_operator(next_token);
				operator_stack.push('$');
			}

			//Otherwise, put the next character back and just process the first
			else
			{
				tokens.putback(repeated_operator);
				process_operator(next_token);
			}
		}

		else
		{
			throw Syntax_Error("Unexpected Character Encountered");
		}
	}

	// Process remaining operators and their respective operands
	while (!operator_stack.empty())
	{
		char op = operator_stack.top();

		if (op == '(' || op == '[' || op == '}')
		{
			throw Syntax_Error("Unmatched open parenthesis");
		}
		else
		{
			eval_op(op);
		}

		operator_stack.pop();
	}
	return operand_stack.top();
}



/** Function to process operators.
@param op The operator
@throws Syntax_Error
*/
void Infix_Parser::process_operator(char op)
{
	//If the stack is empty or the op is an open parentheses, push the op
	if (operator_stack.empty() || (op == '(') || (op == '[') || (op == '{'))
	{
		if (op == ')' || op == ']' || op == '}')
			throw Syntax_Error("Unmatched close parenthesis");
		operator_stack.push(op);
	}

	//If the stack is not empty and the precedence of op is higher than the top, push the op
	// while op is <= top, eval the corresponding operands to the operator
	// This creates a stack of decreasing precedence

	else
	{
		if (precedence(op) > precedence(operator_stack.top()))
		{
			operator_stack.push(op);
		}
		else
		{
			// Pop all stacked operators with equal
			// or higher precedence than op.
			while (!operator_stack.empty()
				&& (operator_stack.top() != '(')
				&& (operator_stack.top() != '[')
				&& (operator_stack.top() != '{')
				&& (precedence(op) <= precedence(operator_stack.top())))
			{
				eval_op(operator_stack.top());
				operator_stack.pop();
			}
			// assert: Operator stack is empty or
			//         top of stack is '(' or current
			//         operator precedence > top of stack operator
			//         precedence;
			if (op == ')')
			{
				if (!operator_stack.empty()
					&& (operator_stack.top() == '('))
				{
					operator_stack.pop();
				}
				else
				{
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else if (op == ']')
			{
				if (!operator_stack.empty()
					&& (operator_stack.top() == '['))
				{
					operator_stack.pop();
				}
				else
				{
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else if (op == '}')
			{
				if (!operator_stack.empty()
					&& (operator_stack.top() == '{'))
				{
					operator_stack.pop();
				}
				else
				{
					throw Syntax_Error("Unmatched close parentheses");
				}
			}
			else
			{
				operator_stack.push(op);
			}
		}
	}
}
/** Implementation of Infix_To_Postfix that processes parentheses.*/