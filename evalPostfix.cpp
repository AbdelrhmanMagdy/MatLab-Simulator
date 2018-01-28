#include <iostream>
#include <stack>
#include <string>

using namespace std;
// Function to evaluate Postfix expression and return output
int EvaluatePostfix(string expression);

// Function to perform an operation and return output for simple calcs.
int PerformOperation(char operation, int operand1, int operand2);
// Function to perform an operation and return output for ttrigonometric functions.
CMatrix PerformOperation(char operation, CMatrix operand1);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);
// Function to verify whether a character is trigonometric function or not.
bool IsTrigonometric(char C);
// Function to verify whether a character is numeric digit.
bool IsNumericDigit(char C);
// Function to verify whether a character is matrix object.
bool IsMatrix(char C);

int main()
{
return 0;
}
int EvaluatePostfix(string expression)
{
    stack <CMatrix> S;

    for (int i = 0; i < expression.length(); i++)
    {

        if (expression[i] == ' ' || expression[i] == ',')
            continue;
        else if (IsTrigonometric(expression[i]))
        {
            CMatrix operand1 = S.top();
            S.pop();
            CMatrix result = PerformOperation(expression[i], operand1);
            S.push(result);
        }
        else if (IsOperator(expression[i]))
        {
            CMatrix operand2 = S.top();
            S.pop();
            CMatrix operand1 = S.top();
            S.pop();
            CMatrix result = PerformOperation(expression[i], operand1, operand2);
            S.push(result);
        }
        else if (IsNumericDigit(expression[i]))
        {
            int operand = 0;
            while (i < expression.length() && IsNumericDigit(expression[i]))
            {
                operand = (operand * 10) + (expression[i] - '0');
                i++;
            }
            i--;
            CMatrix result(operand);
            S.push(result);
        }
        else if (IsMatrix(expression[i]))
        {

            S.push(getMatrix(expression[i]););
        }
    }
    return S.top();
}

bool IsNumericDigit(char C)
{
    if (C >= '0' && C <= '9')
        return true;
    return false;
}
bool IsTrigonometric(char C)
{
    if (C == 's' || C == 'c' || C == 't' || C == 'q')
        return true;

    return false;
}
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/')
        return true;

    return false;
}
bool IsMatrix(char C)
{
    if ()
        return true;

    return false;
}
CMatrix PerformOperation(char operation, CMatrix operand1, CMatrix operand2)
{
    if (operation == '+')
        return operand1.add(operand2);
    else if (operation == '-')
        return operand1.sub(operand2);
    else if (operation == '*')
        return operand1.mult(operand2);
    else if (operation == '/')
        return operand1.div(operand2);
    else
        cout << "Unexpected Error with simple calc perform operation\n"<<endl;
    return -1;
}
CMatrix PerformOperation(char operation, CMatrix operand1)
{
    if (operation == 's')
        return operand1.msin(operand2);
    else if (operation == 'c')
        return operand1.mcos(operand2);
    else if (operation == 't')
        return operand1.mtan(operand2);
    else if (operation == 'q')
        return operand1.msqrt(operand2);
    else
        cout << "Unexpected Error with trinogometric calc perform operation\n";
    return -1;
}