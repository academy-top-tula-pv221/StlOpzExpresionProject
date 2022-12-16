#include "MathExpression.h"

string& MathExpression::Expression()
{
	return expression;
}

string& MathExpression::ExpressionOpz()
{
    return expressionOpz;
}

double& MathExpression::operator[](const char* varName)
{
    if (variables.find(varName) == variables.end())   
        variables.emplace(varName, 0.0);
    
    return variables[varName];
}

double& MathExpression::operator[](string varName)
{
    if (variables.find(varName) == variables.end())
        variables.emplace(varName, 0.0);

    return variables[varName];
}

int MathExpression::BracketsCheck()
{
    int position{};
    const string brackets = "()[]{}";
    const string bracketsOpen = "([{";
    const string bracketsClose = ")]}";
    stack<char> bracketsStack;

    while (position < expression.length())
    {
        // strchr(brackets.c_str(), expresion[position]);

        if (brackets.find(expression[position]) == string::npos)
        {
            position++;
            continue;
        }

        if (bracketsOpen.find(expression[position]) != string::npos)
        {
            bracketsStack.push(expression[position]);
            position++;
            continue;
        }

        if (bracketsStack.empty())
            return position;

        int typeClose = bracketsClose.find(expression[position]);
        int typeOpen = bracketsOpen.find(bracketsStack.top());

        if (typeClose != typeOpen)
            return position;

        bracketsStack.pop();

        position++;
    }

    return ((bracketsStack.empty()) ? -1 : position);
}

void MathExpression::OpzCreate()
{
    int position{};
    const string bracketsOpen = "([{";
    const string bracketsClose = ")]}";
    const string operatorsAdditive = "+-";
    const string operatorsMultiplex = "*/";
    
    stack<char> operatorsStack;

    while (position < expression.length())
    {
        //пропускаем пробелы
        if (expression[position] == ' ')
        {
            position++;
            continue;
        }

        // переносим числа в ОПЗ
        if (isdigit(expression[position]) || expression[position] == '.')
        {
            string number = "";
            while (position < expression.length() &&
                (isdigit(expression[position]) ||
                expression[position] == '.' ||
                tolower(expression[position]) == 'e'))
            {
                if (tolower(expression[position]) == 'e' &&
                    expression[position + 1] == '-')
                {
                    number.push_back(expression[position]);
                    number.push_back(expression[position + 1]);
                    position += 2;
                }
                number.push_back(expression[position]);
                position++;
            }
            number.push_back('#');
            expressionOpz.append(number);
            continue;
        }

        // переменные в числа и в строку
        if (isalpha(expression[position]))
        {
            string varName;
            while (position < expression.length() &&
                        (isalnum(expression[position]) ||
                        expression[position] == '_'))
                varName.push_back(expression[position++]);

            double number = variables[varName];
            expressionOpz.append(to_string(number) + "#");
            continue;
        }

        // открывающася скобка -> в стек
        if (bracketsOpen.find(expression[position]) != string::npos)
            operatorsStack.push(expression[position]);

        // закрывающася скобка -> выталкиваем операторы из стека в ОПЗ
        if (bracketsClose.find(expression[position]) != string::npos)
        {
            while (!operatorsStack.empty()
                && bracketsOpen.find(operatorsStack.top()) == string::npos)
            {
                expressionOpz.push_back(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.pop();
        }

        // операторы * и /
        if (operatorsMultiplex.find(expression[position]) != string::npos)
        {
            while (!operatorsStack.empty()
                && operatorsMultiplex.find(operatorsStack.top()) != string::npos)
            {
                expressionOpz.push_back(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.push(expression[position]);
        }

        // операторы + и -
        if (operatorsAdditive.find(expression[position]) != string::npos)
        {
            while (!operatorsStack.empty()
                && bracketsOpen.find(operatorsStack.top()) == string::npos)
            {
                expressionOpz.push_back(operatorsStack.top());
                operatorsStack.pop();
            }
            operatorsStack.push(expression[position]);
        }
        position++;
    }
    while (!operatorsStack.empty())
    {
        expressionOpz.push_back(operatorsStack.top());
        operatorsStack.pop();
    }
}

double MathExpression::OpzCalculate()
{
    stack<double> numbersStack;
    int position{};
    const string operators = "+-*/";

    while (position < expressionOpz.length())
    {
        // число -> в стек
        if (isdigit(expressionOpz[position]) || expressionOpz[position] =='.')
        {
            string number;
            while (position < expressionOpz.length()
                        && expressionOpz[position] != '#')
                number.push_back(expressionOpz[position++]);
            numbersStack.push(stod(number));
            position++;
            continue;
        }

        // знак операции
        if (operators.find(expressionOpz[position]) != string::npos)
        {
            double result{};
            double operandRight{ numbersStack.top() };
            numbersStack.pop();
            double operandLeft{ numbersStack.top() };
            numbersStack.pop();

            switch (expressionOpz[position])
            {
            case '+': result = operandLeft + operandRight; break;
            case '-': result = operandLeft - operandRight; break;
            case '*': result = operandLeft * operandRight; break;
            case '/': result = operandLeft / operandRight; break;
            default:
                break;
            }

            numbersStack.push(result);
        }
        position++;
    }
    return numbersStack.top();
}

double MathExpression::Calculate()
{
    OpzCreate();
    return OpzCalculate();
}

