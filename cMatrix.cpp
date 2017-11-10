#include "stdarg.h"
#include "string.h"
#include "cMatrix.h"
#include "stdio.h"
#include <iostream>

CMatrix::CMatrix(){
    nR = nC = 0;
    values = NULL;
}

CMatrix::CMatrix(CMatrix &x){
    copy(x);
}
CMatrix::~CMatrix(){
    reset();    
}

void CMatrix::copy(CMatrix &x)
{
    reset();
    this->nR = x.nR;
    this->nC = x.nC;
    values = new double*[nR]; 

    for (int i=0; i<this->nR; i++){
        values[i] = new double[nC];
        
        for (int j=0; j<this->nC; j++){
            values[i][j] = x.values[i][j];
        }
    }
}
void CMatrix::reset()
{
    if (values)
    {
        for (int i = 0; i < this->nR; i++)
        {
            delete[] values[i];
        }
        delete[] values;
    }
    nR = nC = 0;
    values = NULL;
}
// CMatrix::CMatrix(int nR, int nC, double initVal)
// {
//     reset();
//     this->nR = nR;
//     this->nC = nC;
//     values = new double *[nR];

//     for (int i = 0; i < this->nR; i++)
//     {
//         values[i] = new double[nC];

//         for (int j = 0; j < this->nC; j++)
//         {
//             values[i][j] = initVal;
//         }
//     }
// }
CMatrix::CMatrix(int nR, int nC)
{
    this->nR = nR;
    this->nC = nC;
    values = new double *[nR];

    for (int i = 0; i < nR; i++)
    {
        values[i] = new double[nC];

        for (int j = 0; j < nC; j++)
        {
            values[i][j] = 0;
        }
    }
}
CMatrix::CMatrix(int nR, int nC, double first, ...){
    this->nR = nR;
    this->nC = nC;
    if((nR*nC)==0){values=NULL; return;}
    values = new double*[nR];
    va_list va;
    va_start(va, first);
    for(int iR=0;iR<nR;iR++)
    {
        values[iR] = new double[nC];
        for(int iC=0;iC<nC;iC++)
        {
            if (iR == 0 && iC == 0) values[iR][iC] = first;
            else
            values[iR][iC] = va_arg(va, double);
        }
    }
    va_end(va);
}

void CMatrix::display(){
    printf("nR = %d\n",nR);
    printf("nC = %d\n",nC);
    for (int iR=0; iR<this->nR; iR++){
        for (int iC=0; iC<this->nC; iC++){

            printf("%.1f \t",values[iR][iC]);
        }
        printf("\n");
    }
}

CMatrix CMatrix::transpose(){
    CMatrix result(nC, nR);

    for (int iR = 0; iR < result.nR; iR++)
    {
        for (int iC = 0; iC < result.nC; iC++)
        {
            result.values[iR][iC] = values[iC][iR];
        }
    }
    // result.display();
    return result;
}

void CMatrix::add(CMatrix &x){
    if (x.nR != nR || x.nC != nC){throw("Invalid Matrix Addition coulmns and rows must be equal in the two matrices");}
    for (int iR = 0; iR < nR; iR++)
    {
        for (int iC = 0; iC < nC; iC++)
        {
            values[iR][iC] += x.values[iR][iC];
        }
    }
}
void CMatrix::sub(CMatrix &x)
{
    if (x.nR != nR || x.nC != nC)
    {
        throw("Invalid Matrix Substraction coulmns and rows must be equal in the two matrices");
    }
    for (int iR = 0; iR < nR; iR++)
    {
        for (int iC = 0; iC < nC; iC++)
        {
            values[iR][iC] -= x.values[iR][iC];
        }
    }
}

void CMatrix::mult(CMatrix &x){
    if( x.nR != nC || x.nC != nR ){
        throw("Invalid Matrix Multiplication");
    }
    CMatrix temp(nR, x.nC);
    for (int iR = 0; iR < temp.nR; iR++)
        for (int iC = 0; iC < temp.nC; iC++)
        {
            for (int k = 0; k < x.nC; k++)
                temp.values[iR][iC] += values[iR][k] * x.values[k][iC];
        }
    copy(temp);
}

CMatrix CMatrix::coMatrix(int r, int c){
    CMatrix temp(nR-1,nC-1);
    int r_index = 0, c_index ;
    for (int iR = 0; iR < nR; iR++){
        if (iR==r) continue;
        c_index = 0;
        for (int iC = 0; iC < nC; iC++)
        {
            if (iC==c) continue;
            temp.values[r_index][c_index] = values[iR][iC];
            c_index++;
        }
        r_index++;
    }
    temp.display();
    return temp;
}

CMatrix CMatrix::operator= (CMatrix &x)
{
    reset();
    copy(x);
    return *this;
}
CMatrix CMatrix::operator+(CMatrix &x){
    add(x);
    return *this;
}
CMatrix CMatrix::operator-(CMatrix &x)
{
    sub(x);
    return *this;
}
CMatrix CMatrix::operator*(CMatrix &x)
{
    mult(x);
    return *this;
}