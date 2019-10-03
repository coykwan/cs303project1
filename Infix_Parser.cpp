/** Implementation of Infix_To_Postfix that processes parentheses.*/

#include "Infix_Parser.h"
#include <sstream>
#include <cctype>
#include <iostream>
using std::string;
using std::istringstream;
using std::isdigit;

const string Infix_Parser::OPERATORS = "+-*/%()[]{}";
const int Infix_Parser::PRECEDENCE[] = { 1, 1, 2, 2, 2, -1, -1, -1, -1, -1, -1 };

void Infix_Parser::eval_op(char op)
{

  if (this -> operand_stack.empty())
    throw Syntax_Error("Operand stack is empty");

  int rhs = this -> operand_stack.top();
  this -> operand_stack.pop();

  if (this -> operand_stack.empty())
    throw Syntax_Error("Operand stack is empty");

  int lhs = this -> operand_stack.top();
  this -> operand_stack.pop();
  int result = 0;
  switch(op)
  {
  case '+' :
	  result = lhs + rhs;
      break;
  case '-' :
	  result = lhs - rhs;
      break;
  case '*' :
	  result = lhs * rhs;
	  break;
  case '/' :
	  result = lhs / rhs;
	  break;
  case '%' :
	  result = lhs % rhs;
	  break;
  }
  operand_stack.push(result);
}



int Infix_Parser::eval(const std::string& expression)
{
  // Be sure both stacks are empty
  while (!operand_stack.empty())
    operand_stack.pop();

  while(!operator_stack.empty())
	  operator_stack.pop();

  // Process each token
  istringstream tokens(expression);
  char next_token;
  while (tokens >> next_token)
  {
	  if (isdigit(next_token)) //really we want this to be if it's a binary operator
	  {
		  int operand = next_token - '0';
		  this -> operand_stack.push(operand);
	  }
	  else if (is_operator(next_token))
	  {
		  process_operator(next_token);
	  }
	  else
	  {
		  throw Syntax_Error("Unexpected Character Encountered");
	  }
  }

 // std::cout << this -> operand_stack.top();

  // Process remaining operators and their respective operands
    //** CHANGE THIS
  while (!operator_stack.empty())
  {
      char op = operator_stack.top();

      if (op == '(' || op == '[' || op == '}')
      {
        throw Syntax_Error("Unmatched open parenthesis");
      }
      // EVALUATE ANY REMAINING OPERATORS
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
  // ****while op is <= top, eval the corresponding operands to the operator
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
        //THIS IS WHERE WE WANT TO EVALUATE THE OPERAND STACK USING THE OPERATOR(S)
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

