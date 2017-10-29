#include "stdarg.h"
#include "string.h"
class CMatrix
{
int nR, nC;
double** values;
public:
CMatrix();
CMatrix(int nR, int nC, double first, ...);
void reset();
};



CMatrix::CMatrix(){
    nR = nC = 0;
    values = NULL;
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
            values[iR][iC] = (iC==0&&iR==0)?first:va_arg(va, double);
        }
    }
    va_end(va);
}