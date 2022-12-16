#include <iostream>
#include "MathExpression.h"

using namespace std;

int main()
{
    // (1 / (2 - 3) + (4 + 5) * 6) / 7
    MathExpression expr("sin(5) + 6");

    expr["a"] = 10;
    expr["b"] = 20;
    expr["a"] = 5;

    cout << expr["a"] << " " << expr["b"] << "\n";

    cout << expr.Expression() << "\n";
    cout << expr.BracketsCheck() << "\n";

    expr.OpzCreate();
    cout << expr.ExpressionOpz() << "\n";
    cout << expr.OpzCalculate() << "\n";

}
