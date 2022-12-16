#pragma once

#include <iostream>
#include <string>
#include <map>
#include <stack>

using namespace std;

class MathExpression
{
	string expression;
	map<string, double> variables;

	string expressionOpz;
public:
	MathExpression() : expression{ "" } {};
	MathExpression(string expression) 
		: expression{ expression } {};
	MathExpression(const char* expression) 
		: expression{ string(expression) } {};

	string& Expression();
	string& ExpressionOpz();
	double& operator[](const char* varName);
	double& operator[](string varName);

	int BracketsCheck();
	void OpzCreate();
	double OpzCalculate();
	double Calculate();
};

