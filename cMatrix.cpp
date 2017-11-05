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


CMatrix::CMatrix(int nR, int nC, ...){
    this->nR = nR;
    this->nC = nC;
    if((nR*nC)==0){values=NULL; return;}
    values = new double*[nR];
    va_list va;
    va_start(va, nC);
    for(int iR=0;iR<nR;iR++)
    {
        values[iR] = new double[nC];
        for(int iC=0;iC<nC;iC++)
        {
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

