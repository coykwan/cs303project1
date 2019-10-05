/** Implementation of Infix_To_Postfix that processes parentheses.*/

#include "Infix_Parser.h"
#include <sstream>
#include <cctype>
#include <iostream>
#include <cmath>
using std::string;
using std::istringstream;
using std::isdigit;

const string Infix_Parser::OPERATORS = "+-~*/%()[]{}^<>";
const int Infix_Parser::PRECEDENCE[] = { 1, 1, 1, 2, 2, 2, -1, -1, -1, -1, -1, -1, 3, 0, 0 };

//*******************************************************************
// A function to check if the expression meets infix syntax
// if it does not, an appropriate exception will be thrown
// if it does, true is returned.
//******************************************************************
bool Infix_Parser::is_infix(const std::string& expression)
{
	//Checks if the expression starts with a binary operator.
	if(expression.at(0) == '+'
			|| expression.at(0) == '-'
			|| expression.at(0) == '/'
			|| expression.at(0) == '*'
			|| expression.at(0) == '^'
			|| expression.at(0) == '%'
			|| expression.at(0) == '<'
			|| expression.at(0) == '>')
	{
		throw Syntax_Error ("Expression cannot start with a binary operator @ char "
				+ std::to_string(char_count));
	}

	//Checks to see if there are double binary operators or a unary operator followed by a binary operator
	for(long long unsigned int i = 1; i < expression.size(); i++)
	{
		if(is_operator(expression.at(i-1)) && is_operator(expression.at(i)))
		{
			if((expression.at(i-1) == '-' && expression.at(i) == '-')
				|| (expression.at(i-1) == '+' && expression.at(i) == '+')
				|| (expression.at(i-1) == '~' && expression.at(i) == '~')
				)
			{
				break;
			}
			else if((expression.at(i-1) == '~' && expression.at(i) != '~')
					&& expression.at(i) != '('
					&& expression.at(i) != '{'
					&& expression.at(i) != '[')
			{
				throw Syntax_Error("A unary operator cannot be followed by a binary operator @ char "
						+ std::to_string(i));
			}
			else
			{
				throw Syntax_Error ("Two binary operators in a row @ char "
						+ std::to_string(i));
			}
		}
		//this else if pretty much doesn't work.
		else if (isdigit(expression.at(i-1)))
       {
           int value;
           char next;
           istringstream tokens(expression);
           tokens >> value;
           tokens >> next;
           if(isdigit(next))
           {
        	   string find = " ";
        	   find.push_back(next);
        	   throw Syntax_Error ("Two operands in a row @ char "
        			   + std::to_string(expression.find(find)));
        	   //returns the index of the space before the 2nd operand
           }
       }
	}
	// 4 main checks:
	// a) 2 operands in a row (sorta)
	// b) 2 binary operators in a row (done)
	// c) can't start with binary operator (done)
	// d) unary operator can't be followed by a binary operator (done)
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
        throw Syntax_Error("Operand stack is empty");

    int rhs = this->operand_stack.top();
    this->operand_stack.pop();

    if (this->operand_stack.empty())
        throw Syntax_Error("Operand stack is empty");

    int lhs = this->operand_stack.top();
    this->operand_stack.pop();
    int result = 0;
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
    	if (rhs == 0)
    	{
    		throw Syntax_Error("Division by 0 @ char"
    				+ std::to_string(char_count));
    	}
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

        //************************************************************************
        //NEED TO ADD OTHER OPERATORS HERE!!!!
        //Probably going to want to have a check for Binary vs Unary operators
        //And set up another switch case for the unary ones!
        //************************************************************************
    }
    operand_stack.push(result);
}



int Infix_Parser::eval(const std::string& expression)
{
    is_infix(expression); //checks if the expression is infix. if it isn't, an exception will be thrown.
    char_count = 0;
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
         if (isdigit(next_token))
        {
            tokens.putback(next_token);
            int value;

            tokens >> value;
            this->operand_stack.push(value);
        }

         else if (next_token == '~')
         {

             int value;

             tokens >> value;

             value = -(value);
             this->operand_stack.push(value);
         }

        else if (is_operator(next_token))
        {
            process_operator(next_token);
        }

        else
        {
            throw Syntax_Error("Unexpected Character Encountered @ char "
            		+ std::to_string(char_count));
        }
         char_count++;
    }

    // Process remaining operators and their respective operands
    while (!operator_stack.empty())
    {
        char op = operator_stack.top();

        if (op == '(' || op == '[' || op == '}')
        {
            throw Syntax_Error("Unmatched open parenthesis @ char "
            		+ std::to_string(char_count));
        }
        // EVALUATE ANY REMAINING OPERATORS
        else
        {
            eval_op(op);
        }
        operator_stack.pop();
    }
    int result = operand_stack.top();
    if (!operand_stack.empty())
    {
    	throw Syntax_Error("Operand stack should be empty.");
    }
    return result;
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
            throw Syntax_Error("Unmatched close parenthesis @ char "
            		+ std::to_string(char_count));
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
            if (op == ')') {
                if (!operator_stack.empty()
                    && (operator_stack.top() == '('))
                {
                    operator_stack.pop();
                }
                else
                {
                    throw Syntax_Error("Unmatched close parentheses @ char "
                    		+ std::to_string(char_count));
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
                    throw Syntax_Error("Unmatched close parentheses @ char "
                    		+ std::to_string(char_count));
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
                    throw Syntax_Error("Unmatched close parentheses @ char "
                    		+ std::to_string(char_count));
                }
            }
            else
            {
                operator_stack.push(op);
            }
        }
    }
}
