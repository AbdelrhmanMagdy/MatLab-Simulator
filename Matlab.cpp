//
// Created by Mamdouh El Nakeeb on 11/26/17.
//
using namespace std;
#include "Matlab.h"
CMatrix temp_matrices[10];
int n = 0;
int findMatrix(CMatrix *temp_matrices, char name, int n)
{
    n=2;
    for (int i = 0; i < n; i++) {
        if (temp_matrices[i].getName() == name){
            return i;}
    }

    return  -1;

}

void openFile(char* path) {

    std::string matStr = "";
    char operation = 'a';
    int matNo = 0;
    bool newMat = false;
    std::string matrixStr = "";
    std::string constNo = "";

    std::ifstream fileData(path);

    std::string fileLine;

    while (getline(fileData, fileLine)){

        for (int i = 0; i < fileLine.length(); i++){

            newMat = false;

            if (((int) fileLine[i] > 96 && (int) fileLine[i] < 123) || ((int) fileLine[i] > 64 && (int) fileLine[i] < 91)){

                if (findMatrix(temp_matrices, fileLine[i], matNo) == -1){

                    CMatrix tempMat;
                    tempMat.setName(fileLine[i]);
                    temp_matrices[matNo] = tempMat;

                    operation = 'a';

                    matNo++;

                }

                matStr += fileLine[i];

            }
            else if (fileLine[i] == '['){

                newMat = true;

                operation = 'a';

                i++;

                while (fileLine[i] != ']'){
                    matrixStr += fileLine[i];
                    i++;

                    if(i >= fileLine.length()){
                        getline(fileData, fileLine);
                        i = 0;
                    }
                }

                if (matrixStr[matrixStr.length() - 1] == ';'){
                    matrixStr = matrixStr.substr(0, matrixStr.length() - 1);
                }
                else if (matrixStr[matrixStr.length() - 2] == ';'){
                    matrixStr = matrixStr.substr(0, matrixStr.length() - 2);
                }

                temp_matrices[matNo - 1].setValues(matrixStr);
                matrixStr = "";
                break;

            }
            else if (fileLine[i] == '+' || fileLine[i] == '-' || fileLine[i] == '*' || fileLine[i] == '/' || fileLine[i] == '\''){

                operation = fileLine[i];

                if (fileLine[i] == '/' && fileLine[i - 1] == '.'){
                    operation = 'd';
                }
                else if (fileLine[i] == '*' && fileLine[i - 1] == '.'){
                    operation = 'm';
                }
            }

            else if (fileLine[i] == ' ' || fileLine[i] == '\r' || fileLine[i] == '\n' || fileLine[i] == '='){
                continue;
            }
            else if ((int) fileLine[i] > 47 && (int) fileLine[i] < 58){

                while (fileLine[i] != ' '){
                    constNo += fileLine[i];
                    i++;
                }

            }

        }

        if (matStr.length() == 1 && !newMat){
            operation = 'p';
        }

        if (operation != 'a'){

            CMatrix mat1, mat2, mat3;
            int matIndex = 0;

            switch (operation){

                case '+':

                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    mat3 = mat1 + mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    mat3.display();

                    temp_matrices[matIndex] = mat3;

                    break;
                case '-':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    mat3 = mat1 - mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    mat3.display();
                    temp_matrices[matIndex] = mat3;

                    break;
                case '*':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    mat3 = mat1 * mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    mat3.display();
                    temp_matrices[matIndex] = mat3;

                    break;
                case '/':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    try {

                        mat3 = mat1 / mat2;

                        mat3.setName(temp_matrices[matIndex].getName());

                        mat3.display();
                        temp_matrices[matIndex] = mat3;
                    }
                    catch ( const char* e){
                        printf("%s",e);
                    }

                    break;

                case '\'':
                    try{
                        mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];

                        matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                        mat2 = mat1.transpose();

                        mat2.setName(temp_matrices[matIndex].getName());

                        mat2.display();
                        temp_matrices[matIndex] = mat2;
                    }
                    catch (const char* e){
                        printf("%s",e);
                    }


                    break;
                case 'd':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    //mat2 ./ mat1
                    mat2 = mat1.divElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'm':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    //mat2 .* mat1
                    mat2 = mat1.multElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'p':
                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);
                    mat1 = temp_matrices[matIndex];

                    if (mat1.getCols() * mat1.getRows() == 0){
                        printf("No matrix found with the name %c \n", matStr[0]);
                    }
                    else{
                        mat1.display();
                    }

                    break;
            }



        }

        matStr = "";
        n++;
    }


    if (fileData.is_open()){
        fileData.close();
    }


}


void cline(){

    CMatrix temp_matrices[10];
    std::string matStr = "";
    char operation = 'a';
    int n = 0, matNo = 0;
    bool newMat = false;
    std::string matrixStr = "";
    std::string constNo = "";


    std::string fileLine;

    std::cout << "Type 'exit' when finished" << std::endl;

    while (getline(std::cin, fileLine)){

        if (fileLine == "exit"){
            break;
        }

        for (int i = 0; i < fileLine.length(); i++){

            newMat = false;

            if (((int) fileLine[i] > 96 && (int) fileLine[i] < 123) || ((int) fileLine[i] > 64 && (int) fileLine[i] < 91)){

                if (findMatrix(temp_matrices, fileLine[i], matNo) == -1){

                    CMatrix tempMat;
                    tempMat.setName(fileLine[i]);
                    temp_matrices[matNo] = tempMat;

                    operation = 'a';

                    matNo++;

                }

                matStr += fileLine[i];

            }
            else if (fileLine[i] == '['){

                newMat = true;

                operation = 'a';

                i++;

                while (fileLine[i] != ']'){
                    matrixStr += fileLine[i];
                    i++;

                    if(i >= fileLine.length()){
                        getline(std::cin, fileLine);
                        i = 0;
                    }
                }

                if (matrixStr[matrixStr.length() - 1] == ';'){
                    matrixStr = matrixStr.substr(0, matrixStr.length() - 1);
                }
                else if (matrixStr[matrixStr.length() - 2] == ';'){
                    matrixStr = matrixStr.substr(0, matrixStr.length() - 2);
                }

                temp_matrices[matNo - 1].setValues(matrixStr);
                matrixStr = "";
                break;

            }
            else if (fileLine[i] == '+' || fileLine[i] == '-' || fileLine[i] == '*' || fileLine[i] == '/' || fileLine[i] == '\''){

                operation = fileLine[i];

                if (fileLine[i] == '/' && fileLine[i - 1] == '.'){
                    operation = 'd';
                }
                else if (fileLine[i] == '*' && fileLine[i - 1] == '.'){
                    operation = 'm';
                }
            }

            else if (fileLine[i] == ' ' || fileLine[i] == '\r' || fileLine[i] == '\n' || fileLine[i] == '='){
                continue;
            }
            else if ((int) fileLine[i] > 47 && (int) fileLine[i] < 58){

                while (fileLine[i] != ' '){
                    constNo += fileLine[i];
                    i++;
                }

            }

        }

        if (matStr.length() == 1 && !newMat){
            operation = 'p';
        }

        if (operation != 'a'){

            CMatrix mat1, mat2, mat3;
            int matIndex = 0;

            switch (operation){

                case '+':

                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    mat3 = mat1 + mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    mat3.display();

                    temp_matrices[matIndex] = mat3;

                    break;
                case '-':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    mat3 = mat1 - mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    mat3.display();
                    temp_matrices[matIndex] = mat3;

                    break;
                case '*':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    mat3 = mat1 * mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    mat3.display();
                    temp_matrices[matIndex] = mat3;

                    break;
                case '/':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];
                    mat2 = temp_matrices[findMatrix(temp_matrices, matStr[2], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    try {

                        mat3 = mat1 / mat2;

                        mat3.setName(temp_matrices[matIndex].getName());

                        mat3.display();
                        temp_matrices[matIndex] = mat3;
                    }
                    catch (const char* e){
                        printf("%s", e);
                    }

                    break;

                case '\'':
                    try{
                        mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];

                        matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                        mat2 = mat1.transpose();

                        mat2.setName(temp_matrices[matIndex].getName());

                        mat2.display();
                        temp_matrices[matIndex] = mat2;
                    }
                    catch (const char* e){
                        printf("%s", e);
                    }

                    break;
                case 'd':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    //mat2 ./ mat1
                    mat2 = mat1.divElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'm':
                    mat1 = temp_matrices[findMatrix(temp_matrices, matStr[1], matNo)];

                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);

                    //mat2 .* mat1
                    mat2 = mat1.multElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'p':
                    matIndex = findMatrix(temp_matrices, matStr[0], matNo);
                    mat1 = temp_matrices[matIndex];

                    if (mat1.getCols() * mat1.getRows() == 0){
                        printf("No matrix found with the name %c \n", matStr[0]);
                    }
                    else{
                        mat1.display();
                    }

                    break;
            }

        }

        matStr = "";
        n++;
    }

}


// Function to convert Infix expression to Postfix expression
std::string InfixToPostfix(std::string expression) {
    // Declaring a Stack from Standard template library in C++.
    std::stack<char> S;
    std::string postfix = ""; // Initialize postfix as empty string.
    for(int i = 0;i< expression.length();i++) {

        // Scanning each character from left.
        // If character is a delimitter, move on.
        if(expression[i] == ' ') {
            if(postfix[postfix.length() - 1] != ' ')
                postfix += ' ';
            continue;
        }
            // If character is operator, pop two elements from stack, perform operation and push the result back.
        else if(IsOperator(expression[i]))
        {
            while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), expression[i]))
            {
                if(postfix[postfix.length() - 1] != ' ')
                    postfix += ' ';

                postfix+= S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
            // Else if character is an operand
        else if(IsOperand(expression[i]))
        {
            char oper = ' ';
            if (expression[i] == 's'){
                if(expression[i + 1] == 'i' && expression[i + 2] == 'n'){
                    oper = 's';
                    i = i + 2;
                }
                else if(expression[i + 1] == 'q' && expression[i + 2] == 'r' && expression[i + 3] == 't'){
                    oper = 'q';
                    i = i + 3;
                }
            }
            else if (expression[i] == 'c'){
                if(expression[i + 1] == 'o' && expression[i + 2] == 's'){
                    oper = 'c';
                    i = i + 2;
                }
            }
            else if (expression[i] == 't'){
                if(expression[i + 1] == 'a' && expression[i + 2] == 'n'){
                    oper = 't';
                    i = i + 2;
                }
            }
            else if (expression[i] == 'l'){
                if(expression[i + 1] == 'o' && expression[i + 2] == 'g'){
                    oper = 'l';
                    i = i + 2;
                }
                else if(expression[i + 1] == 'n'){
                    oper = 'n';
                    i = i + 1;
                }
            }
            else if (expression[i] == '.'){
                if (expression[i + 1] == '/'){
                    oper = 'd';
                    i = i + 1;
                }
                else if (expression[i + 1] == '*'){
                    oper = 'm';
                    i = i + 1;
                }
                else if (expression[i + 1] == '+'){
                    oper = 'a';
                    i = i + 1;
                }
                else if (expression[i + 1] == '-'){
                    oper = 'u';
                    i = i + 1;
                }
                else if (expression[i + 1] == '^'){
                    oper = 'p';
                    i = i + 1;
                }
                else{
                    postfix +=expression[i];
                }
            }
            else{
                postfix +=expression[i];
            }

            if (oper != ' '){
                while(!S.empty() && S.top() != '(' && HasHigherPrecedence(S.top(), oper))
                {
                    if(postfix[postfix.length() - 1] != ' ')
                        postfix += ' ';

                    postfix+= S.top();
                    S.pop();
                }
                S.push(oper);
            }
        }

        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }

        else if(expression[i] == ')')
        {
            while(!S.empty() && S.top() !=  '(') {

                if(postfix[postfix.length() - 1] != ' ')
                    postfix += ' ';

                postfix += S.top();
                postfix += ' ';
                S.pop();
            }
            S.pop();
        }

        if(!IsOperand(expression[i]) && postfix[postfix.length() - 1] != ' ')
            postfix += ' ';
    }

    while(!S.empty()) {
        postfix += ' ';
        postfix += S.top();
        S.pop();
    }

    if(postfix[0] == ' ')
        postfix = postfix.substr(1, postfix.length() - 1);
    if(postfix[postfix.length() - 1] == ' ')
        postfix = postfix.substr(0, postfix.length() - 2);

    return postfix;
}

// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand(char C) {
    if(C >= '0' && C <= '9') return true;
    if(C >= 'a' && C <= 'z') return true;
    if(C >= 'A' && C <= 'Z') return true;
    if(C == '.') return true;
    return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C)
{
    if (C == '+' || C == '-' || C == '*' || C == '/' || C == '^' || C == 'a' || C == 'p' || C == 'u' || C == 'm' || C == 'd')
    // {   cout<<C<<" operator"<<endl;
     return true;
//  }
 return false;
}
// Function to verify whether an operator is right associative or not.
int IsRightAssociative(char op) {
    if(op == '^') return true;
    return false;
}

bool IsNumericDigit(char C)
{
    if (C >= '0' && C <= '9')
        return true;
    return false;
}
// Function to verify whether a character is trigonometric function or not.
bool IsTrigonometric(char C)
{
    if (C == 's' || C == 'q' || C == 'c' || C == 't' || C == 'l' )
        return true;

    return false;
}
// Function to verify whether a character is matrix object.
bool IsMatrix(char C)
{

    // cout << "find matrix:"<<C<<"  " << findMatrix(temp_matrices, C, n)<<endl;
    // temp_matrices[0].display();
     if (findMatrix(temp_matrices, C, n) != -1) return true;

    return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(char op) {
    int weight = -1;
    switch(op)
    {
        case '+':
            weight = 1;
            break;
        case '-':
            weight = 1;
            break;
        case 'a': // .+
            weight = 2;
            break;
        case 'u': // .-
            weight = 2;
            break;
        case '*':
            weight = 3;
            break;
        case '/':
            weight = 3;
            break;
        case 'm': // .*
            weight = 3;
            break;
        case 'd': // ./
            weight = 3;
            break;
        case '^':
            weight = 4;
            break;
        case 'p': // .^
            weight = 4;
            break;
        case 's': // sin
            weight = 4;
            break;
        case 'q': // sqrt
            weight = 4;
            break;
        case 'c': // cos
            weight = 4;
            break;
        case 't': // tan
            weight = 4;
            break;
        case 'l': // log
            weight = 4;
            break;
        case 'n': // Ln
            weight = 4;
            break;
    }
    return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(char op1, char op2) {
    int op1Weight = GetOperatorWeight(op1);
    int op2Weight = GetOperatorWeight(op2);

    // If operators have equal precedence, return true if they are left associative.
    // return false, if right associative.
    // if operator is left-associative, left one should be given priority.
    if(op1Weight == op2Weight)
    {
        if(IsRightAssociative(op1)) return false;
        else return true;
    }
    return op1Weight > op2Weight;
}
// Function to evaluate Postfix expression and return output
CMatrix EvaluatePostfix(std::string expression){
    std::stack <CMatrix> S;
    // cout<<expression<<endl;
    for (int i = 0; i < expression.length(); i++)
    {
        // cout<<expression[i]<<endl;
        if (expression[i] == ' ' || expression[i] == ',')
            continue;
        else if (IsTrigonometric(expression[i]))
        {
            CMatrix operand1 = S.top();
            S.pop();
            CMatrix result = solve(operand1,expression[i]);
            S.push(result);
        }
        else if (IsOperator(expression[i]))
        {
            // std::cout << expression[i]<<"  IsOperator" << std::endl;
            CMatrix operand2 = S.top();
            // operand2.display();
            S.pop();
            CMatrix operand1 = S.top();
            // operand1.display();
            S.pop();
            CMatrix result = solve(operand1, expression[i], operand2);
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
            // cout<<operand<<endl;
            CMatrix result(1,1,4,operand);
            // std::cout<<"result is matrix"<<std::endl;
            // result.display();
            S.push(result);
        }
        else if (IsMatrix(expression[i]))
        {
            // cout << expression[i]<<"  Is Matrix" << endl;
            int tempMatIndex = findMatrix(temp_matrices, expression[i] ,n);

            S.push(temp_matrices[tempMatIndex]);
        }
        // cout<<expression[i]<<endl;
    }
    return S.top();
}

CMatrix solve(CMatrix mat1, char op)
{
    CMatrix answer(mat1.getRows(), mat1.getCols());

    if (op == 's')
    {
        answer = Sin(mat1);
    }

    else if(op == 'c')
    {
        answer = Cos(mat1);
    }

    else if(op == 't')
    {
        answer = Tan(mat1);
    }

    // else if(op == 'l')
    // {
    //     answer(log(mat1));
    // }

    // else if(op == 'n')
    // {
    //     answer(ln(mat1));
    // }

    // else if(op == 'q')
    // {
    //     answer(sqrt(mat1));
    // }

    return answer;
}

CMatrix solve(CMatrix mat1, char op, CMatrix mat2)
{
    CMatrix answer(mat1.getRows(), mat1.getCols());
    // mat1.display();
    // mat2.display();
    // cout<<op<<endl;
    if(op == '+')
    {
        answer = mat1 + mat2;
    }

    else if(op == '-')
    {
        answer = mat1 - mat2;
    }

    else if(op == '*')
    {
        answer = mat1 * mat2;
    }

    else if(op == '/')
    {
        answer = mat1 / mat2;
    }

    else if(op == '^')
    {
        answer = mat1 ^ mat2.values[0][0];
    }

    else if(op == 'p')
    {
        // answer = mat1 ^= mat2.values[0][0];
    }

    else if(op == 'a') //.+
    {
        for (int i = 0; i < mat1.nR; i++)
        {
            for (int j = 0; j < mat1.nC; j++)
            {
                answer.values[i][j] = mat1.values[i][j] + mat2.values[0][0];
            }
        }
    }

    else if(op == 'u') //.-
    {
        for (int i = 0; i < mat1.nR; i++)
        {
            for (int j = 0; j < mat1.nC; j++)
            {
                answer.values[i][j] = mat1.values[i][j] - mat2.values[0][0];
            }
        }
    }

    else if(op == 'm') //.*
    {
        for (int i = 0; i < mat1.nR; i++)
        {
            for (int j = 0; j < mat1.nC; j++)
            {
                answer.values[i][j] = mat1.values[i][j] * mat2.values[0][0];
            }
        }
    }

    else if(op == 'd') //./
    {
        for (int i = 0; i < mat1.nR; i++)
        {
            for (int j = 0; j < mat1.nC; j++)
            {
                answer.values[i][j] = mat1.values[i][j] / mat2.values[0][0];
            }
        }
    }

    return answer;
}
// CMatrix PerformOperation(char operation, CMatrix operand1, CMatrix operand2)
// {
//     double x=0;
//     if(operand2.nR == 1 && operand2.nC == 1){
//         x = operand2.values[0][0]; 
//     }
//     if (operation == '+')
//     {
//         return operand1.add(operand2);
//     }
//     else if (operation == '-')
//         return operand1.sub(operand2);
//     else if (operation == '*')
//         return operand1.mult(operand2);
//     else if (operation == '/')
//         return operand1/operand2;
//     else
//         std::cout << "Unexpected Error with simple calc perform operation\n"
//              << std::endl;
//     return operand1;
// }
// CMatrix PerformOperation(char operation, CMatrix operand1)
// {
//     // CMatrix x;
//     // if (operation == 's')
//     //     return Sin(operand2);
//     // else if (operation == 'c')
//     //     return operand1.Cos(operand2);
//     // else if (operation == 't')
//     //     return operand1.Tan(operand2);
//     // else
//     //     std::cout << "Unexpected Error with trinogometric calc perform operation\n";
//     return operand1;
// }