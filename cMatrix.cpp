#include "stdarg.h"
#include "string.h"
#include "cMatrix.h"
#include "stdio.h"
#include <iostream>

CMatrix::CMatrix(){
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

