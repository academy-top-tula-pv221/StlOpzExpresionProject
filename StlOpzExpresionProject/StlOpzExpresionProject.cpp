#include <iostream>
#include <string>
#include <stack>

using namespace std;

int BracketsCheck(string expresion)
{
    int position{};
    const string brackets = "()[]{}";
    const string bracketsOpen = "([{";
    const string bracketsClose = ")]}";
    stack<char> bracketsStack;

    while (position < expresion.length())
    {
        // strchr(brackets.c_str(), expresion[position]);

        if (brackets.find(expresion[position]) == string::npos)
        {
            position++;
            continue;
        }

        if (bracketsOpen.find(expresion[position]) != string::npos)
        {
            bracketsStack.push(expresion[position]);
            position++;
            continue;
        }

        if (bracketsStack.empty())
            return position;

        int typeClose = bracketsClose.find(expresion[position]);
        int typeOpen = bracketsOpen.find(bracketsStack.top());
        
        if (typeClose != typeOpen)
            return position;

        bracketsStack.pop();

        position++;
    }

    return ((bracketsStack.empty()) ? -1 : position);
}

int main()
{
    string expresionMath = "())";

    cout << expresionMath << "\n";
    cout << BracketsCheck(expresionMath) << "\n";
}
