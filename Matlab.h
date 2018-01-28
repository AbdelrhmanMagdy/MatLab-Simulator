//
// Created by Mamdouh El Nakeeb on 11/26/17.
//

#ifndef CMATRIX_PARSE_H
#define CMATRIX_PARSE_H

#include <sstream>
#include <fstream>
#include <iostream>
#include "string.h"
#include "cMatrix.h"

std::string findMatrix(CMatrix *temp_matrices, char name, int n);

std::string itos(int in);

bool subMatrixExist(std::string fileline);


void openFile(char* path);
void cline();


#endif