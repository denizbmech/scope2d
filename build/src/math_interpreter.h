/*
Program:        Math Expression Parser v1.0.
Author:         Deniz Bilgili
		        Technical University of Istanbul, 
				Department of Mechanical Engineering
Date published: 05.2017

This code is shared publicly, under the MIT License. To see the license, please 
refer to the LICENSE.txt file.

Please do not delete this section.
*/


#ifndef MATH_INTERPRETER_H
#define MATH_INTERPRETER_H

#ifndef M_PI
#define M_PI 3.14159265358979323846  /* pi */
#endif // !M_PI

#include <string>
#include <stack>
#include <queue>
#include <sstream>
#include <cmath>
#include <vector>
#include <exception>


struct Variable {
	std::string name;
	double value = 1.0;
};

typedef std::vector<Variable> vector_Variable;
typedef std::vector<std::string> vector_string;
typedef std::vector<double> vector_double;

enum FUNCTION {

	NONE = 0,
	LOG,
	LOG10,
	SIN,
	COS,
	TAN,
	COT,
	ASIN,
	ACOS,
	ATAN,
	ATAN2, // not supported yet
	ACOT,
	DEG,
	RAD,
	SQRT,
	EXP,
	ABS

};

class INPUT_EXPR_SYNTAX_ERROR: public std::exception {

public:
	virtual const char* what() const noexcept {
		return "Syntax error in the input expression.";
	}

};

class BAD_INIT: public std::exception {

public:
	virtual const char* what() const noexcept {
		return "Bad initialization of MathInterpreter object. Input "
			"expression was not set.";
	}

};

class UNKNOWN_VARIABLE: public std::exception {

public:
	UNKNOWN_VARIABLE(const std::string& varName) {
		m_returnMessage = "Variable not found in the input expression: " +
			varName;
	}

	virtual const char* what() const noexcept {
		return m_returnMessage.c_str();
	}

private:
	std::string m_returnMessage;

};

class MathInterpreter {

/*
	Mathematical expression parser and calculator object for real-valued input.
	Works only with real numbers and returns real numbers. Uses the Shunting
	Yard Algorithm.

	How to use:

	A. Without variables
		1. Have the mathematical expression you want to solve stored in a 
		   string in infix notation.
		  
			e.g. std::string expr = "-12.4 + exp(sin(rad(68))) * log10(96)";

		2. Create a MathInterpreter object and call init_with_expr() to
		   initialize the interpreter with the given input expression.
		
			e.g. MathInterpreter inter;
				 inter.init_with_expr(expr);

		4. Call calculate() to calculate the expression and save it in a 
		   double.
		   
			e.g. double result = inter.calculate();

	B. With variables
		1. Have the mathematical expression you want to solve stored in a 
		   string in infix notation. Use apostrophes before and after variable 
		   names to mark variables.

			e.g. std::string expr = "-12.4 + exp(sin(rad('x'))) * log10('y')";
				 //x and y are variables.
		
		2. Create a MathInterpreter object and call init_with_expr() to
		initialize the interpreter with the given input expression.

			e.g. MathInterpreter inter;
			inter.init_with_expr(expr);

		4. Use set_value() to set values for each variable.

			e.g. inter.set_value("x", 12.75);
				 inter.set_value("y", 3.12);

		5. Call calculate() to calculate the expression and save it in a 
		   double.

			e.g. double result = inter.calculate();


	Notes:
		- Function names can be all lowercase or all uppercase.
		- Pi is recognized automatically when entered as a variable.
			e.g. sin(2*'pi'*5) or sin(2*'PI'*5)


	Limitations:
		- Supported operators: +, -, *, /, %, ^
		- Supported functions: Given under enum FUNCTION
		- Only real numbers are supported
		- Results are returned only as double
*/

public:
	MathInterpreter() = default;

	const std::string& input_expr() const { return m_inputExpr; }
	const vector_string& rpn() const { return m_rpn; }

	double calculate();

	void init_with_expr(const std::string& input);
	void set_value(const std::string& varName, const double& varValue);

	virtual ~MathInterpreter() = default;

private:
	std::string m_inputExpr;
	vector_string m_rpn;
	std::string m_calcMap;

	vector_Variable m_vars;

	bool m_isOperator(const std::string::const_iterator& it,
		const std::string::const_iterator& itBegin) const;
	bool m_isOperator(const std::string& token) const;

	bool m_isNumber(const std::string::const_iterator& it,
		const std::string::const_iterator& itBegin) const;
	bool m_isNumber(const std::string& token) const;

	int m_isVariable(const std::string& token) const;
	bool m_variableExists(const std::string& varName) const;

	FUNCTION m_isFunction(const std::string& token) const;

	int m_precedence(const char& op) const;
	int m_precedence(const std::string& op) const;

	double m_calc_operator(double lVal, double rVal, char op) const;
	double m_calc_function(double val, FUNCTION func) const;

	void m_make_rpn();
	void m_make_calc_map();
	void m_init();

	double m_calc_rpn() const;

	std::string m_clear_whitespaces(const std::string& str) const;

};

#endif // !MATH_INTERPRETER_H
