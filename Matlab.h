//
// Created by Mamdouh El Nakeeb on 11/26/17.
//

#ifndef CMATRIX_PARSE_H
#define CMATRIX_PARSE_H

#include <sstream>
#include <fstream>
#include <iostream>
#include<stack>
#include "string.h"
#include "cMatrix.h"

int findMatrix(CMatrix *temp_matrices, char name, int n);

void openFile(char* path);
void cline();

// Function to convert Infix expression to postfix
std::string InfixToPostfix(std::string expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(char operator1, char operator2);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(char C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
bool IsOperand(char C);

#endif