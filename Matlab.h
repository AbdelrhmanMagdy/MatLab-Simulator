//
// Created by Mamdouh El Nakeeb on 11/26/17.
//

#ifndef CMATRIX_PARSE_H
#define CMATRIX_PARSE_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include "string.h"
#include "cMatrix.h"

extern CMatrix temp_matrices[10];
extern int n;

extern int findMatrix(CMatrix *temp_matrices, char name, int n);

void openFile(char *path);
void cline();

// Function to convert Infix expression to postfix
std::string InfixToPostfix(std::string expression);
CMatrix Equation(std::string ex);
// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
bool IsOperand(char C);

// Function to evaluate Postfix expression and return output
CMatrix EvaluatePostfix(std::string expression);

// Function to verify whether a character is trigonometric function or not.
bool IsTrigonometric(char C);
// Function to verify whether a character is numeric digit.
bool IsNumericDigit(char C);
// Function to verify whether a character is matrix object.
extern bool IsMatrix(char C);
////////////////////////////////////////
// Function to perform an operation and return output for simple calcs.
CMatrix solve(CMatrix mat1, char op, CMatrix mat2);
// Function to perform an operation and return output for ttrigonometric functions.
CMatrix solve(CMatrix mat1, char op, CMatrix mat2);
// Function has subMatrix or not
bool subMatrixExist(std::string fileline);
#endif