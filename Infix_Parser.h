#ifndef INFIX_PARSER_H
#define INFIX_PARSER_H

#include "Syntax_Error.h"
#include <string>
#ifdef USEKW
#include "stack.h"  // For KW::stack
#else
#include <stack>    // For standard stack
#endif

class Infix_Parser
{
private:

    // Data fields
    static const std::string OPERATORS;
    static const int PRECEDENCE[];
	#ifdef USEKW
    KW::stack<char> operator_stack;
    KW::stack<int> operand_stack;
	#else
    std::stack<char> operator_stack;
    std::stack<int> operand_stack;
 	 #endif
    int result;

    /** Determines the precedence of an operator.
        @param op The operator
        @return The precedence
    */
    int precedence(char op) const
    {
      return PRECEDENCE[OPERATORS.find(op)];
    }

    /** Determines whether a character is an operator.
        @param ch The character to be tested
        @return true if the character is an operator
    */
    bool is_operator(char ch) const
    {
      return OPERATORS.find(ch) != std::string::npos;
    }

    /** Function to process operators.
        @param op The operator
        @throws Syntax_Error
    */
    void process_operator(char op);

    /** Evaluates the current operator.
        This function pops the two operands off the operand
        stack and applies the operator.
        @param op A character representing the operator
        @throws Syntax_Error if top is attempted on an empty stack
    */
    void eval_op(char op);

public:

    /** Evaluates a postfix expression.
        @param expression The expression to be evaluated
        @return The value of the expression
        @throws Syntax_Error if a syntax error is detected
    */
    int eval(const std::string& expression);

};

#endif
