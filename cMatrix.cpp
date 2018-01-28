#include "stdarg.h"
#include "string.h"
#include "cMatrix.h"
#include "stdio.h"
#include <iostream>
#include <cmath>

using namespace std;
 CMatrix CMatrix:: Sin(const CMatrix &a)
{
    CMatrix temp(a.nR,a.nC);
    for(int i=0;i<a.nR;i++)
    {
        for(int j=0;j<a.nC;j++)
        {
            temp.values[i][j]= sin(a.values[i][j]);

        }

    }


return temp;

}


CMatrix CMatrix:: Cos(const CMatrix &a)
{
    CMatrix temp(a.nR,a.nC);
    for(int i=0;i<a.nR;i++)
    {
        for(int j=0;j<a.nC;j++)
        {
            temp.values[i][j]= cos(a.values[i][j]);

        }

    }


    return temp;

}
CMatrix CMatrix:: Tan(const CMatrix &a)
{
    for (int i = 0; i < a.nR; i++) {
        for (int j = 0; j < a.nC; j++) {
            if ( a.values[i][j]=90 )
                throw "Invalid Matrix tan values can't be equal  90 ";
        }
    }
    
    CMatrix temp(a.nR,a.nC);
    for(int i=0;i<a.nR;i++)
    {
        for(int j=0;j<a.nC;j++)
        {
            temp.values[i][j]= tan(a.values[i][j]);

        }

    }


    return temp;

}


CMatrix CMatrix:: operator ^(int i)
{
    if (nR != nC) throw "Invalid Matrix Subtraction columns and rows must be equal";

    CMatrix temp = *this;

    if(i==0)
    {
        for(int i=0;i<nR;i++)
        {
            for(int j=0;j<nC;j++)
            {
                if(i==j)
                    temp. values[i][j]=1;
                else
                    temp. values[i][j]=0;

            }

        }
    }

    for(int j=2 ; j<=i ; j++)
    {
        temp=temp* *this;
    }


    return temp;

}










CMatrix::CMatrix(){
    nR = nC = 0;
    values = NULL;
}

CMatrix::CMatrix(const CMatrix &x){
    copy(x);
}

void CMatrix::copy(const CMatrix &x)
{
    //reset();
    this->nR = x.nR;
    this->nC = x.nC;
    if ((nR * nC) == 0)
    {
        values = NULL;
        return;
    }
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
        for (int i = 0; i < nR; i++)
        {

            delete[] values[i];
        }
        delete[] values;
    }
    nR = nC = 0;
    values = NULL;
}
CMatrix::CMatrix(int nR, int nC,int initialization, double initializationValue)//need it to initialize matrices with certain values and hamada is important for the compiler to differentiate between this fn and the fn with infinite variables
{
    this->nR = nR;
    this->nC = nC;
    if((nR*nC) == 0) {
        values = NULL;
        return;
    }
    values = new double *[nR];

    for (int iR = 0; iR < nR; iR++)
    {
        values[iR] = new double[nC];
        for (int iC = 0; iC < nC; iC++)
        {
            switch (initialization)
            {
                default:
                    values[iR][iC] = initializationValue;
                    break;
            }
        }
    }
}
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

void CMatrix::addCol(){

    double* newArr = new double [nC + 1];
    if (nC != 0) {
        std::copy(values[nR], values[nR] + (nC + 1), newArr);
        delete[] values[nR];
    }
    values[nR] = newArr;

}

void CMatrix::addRow(){

    double** newArr = new double* [nR + 1];
    newArr[nR] = new double [nC + 1];
    std::copy(values, values + (nR + 1), newArr);
    delete[] values;
    values = newArr;

}

CMatrix::CMatrix(std::string matStr) {

    setValues(matStr);

}

void CMatrix::setValues(std::string matStr)
{



    //

//    nR = 0;
//    nC = 0;
//
//    std::string temp;
//    bool lastCh = false;
//    values = new double *[1];
//    values[0] = new double [1];
//
//    for (int i = 0; i < matStr.length(); i++){
//
//        switch(matStr[i]){
//
//            case ' ':
//                if (lastCh){
//
//                    values[nR][nC] = atof(temp.c_str());
//                    temp = "";
//                    nC++;
//                    values[nR] = new double [nC + 1];
//
//                }
//                lastCh = false;
//                break;
//            case ';':
//                if (i == matStr.length() - 1 || i == matStr.length() - 2)
//                    break;
//
//                if (lastCh){
//                    values[nR][nC] = atof(temp.c_str());
//                    temp = "";
//                }
//
//                lastCh = false;
//                nR++;
//                values = new double *[nR + 1];
//                values[nR] = new double [nC + 1];
//                nC = 0;
//                break;
//
//            default:
//
//                lastCh = true;
//                temp += matStr[i];
//
//                break;
//        }
//
//    }

    //
    nR = 0, nC = 0;


    values = new double *[1];
    values[0] = new double [0];

    std::string tempNo = "";
    int n = 0;
    bool newNo = false;

    for (int i = 0; i < matStr.length(); i++){

        switch(matStr[i]){

            case ' ':
                if (newNo) {
                    addCol();
                    values[nR][nC] = atof(tempNo.c_str());
                    newNo = false;
                    tempNo = "";
                    nC++;
                }
                break;

            case ';':
                addCol();
                values[nR][nC] = atof(tempNo.c_str());
                newNo = false;
                tempNo = "";
                nR++;
                addRow();
                nC = 0;
//                addCol();
                break;

            case '\r':
                break;

            case '\n':
                break;

            case ']':
                break;

            default:
                tempNo += matStr[i];
                newNo = true;
                break;
        }

    }

    addCol();
    values[nR][nC] = atof(tempNo.c_str());
    tempNo = "";
    nR++;
    nC++;

}

void CMatrix::setName(char nme)
{
    this->nme = nme;
}

char CMatrix::getName()
{
    return nme;
}
double **CMatrix::getValues()
{
    return values;
}
int CMatrix::getRows()
{
    return nR;
}

int CMatrix::getCols()
{
    return nC;
}

void CMatrix::display(){

    for (int iR=0; iR<this->nR; iR++){
        for (int iC=0; iC<this->nC; iC++){

            printf("%.4f  \t",values[iR][iC]);
        }
        printf("\n");
    }
    printf("\n");
}


CMatrix CMatrix::add(const CMatrix & x){
    //print error when the number of cols and rows are not the same in the two matrices
    if (x.nR != nR || x.nC != nC)
    {
        throw("Invalid Matrix Addition columns and rows must be equal in the two matrices");
    }

    CMatrix temp(*this);
    //add the values of the two matrices in one temp matrix
    for (int iR = 0; iR < nR; iR++)
    {
        for (int iC = 0; iC < nC; iC++)
        {
            temp.values[iR][iC] += x.values[iR][iC];
        }
    }
    return temp;
}

CMatrix CMatrix::sub(const CMatrix &x)
{
    //print error when the number of cols and rows are not the same in the two matrices
    if (x.nR != nR || x.nC != nC)
    {
        throw("Invalid Matrix Subtraction columns and rows must be equal in the two matrices");
    }
    CMatrix temp(*this);
    //subtract the values of the two matrices in one temp matrix

    for (int iR = 0; iR < nR; iR++)
    {
        for (int iC = 0; iC < nC; iC++)
        {
            temp.values[iR][iC] -= x.values[iR][iC];
        }
    }
    return temp;
}

CMatrix CMatrix::mult(const CMatrix &x){
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
    return temp;
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
    //temp.display();
    return temp;
}

double CMatrix::determinent()
{
    int  indexcolomns, minorrows, minorcolomns;
    double Determinent = 0;
    CMatrix minorMatrix(nR -1, nC - 1);
    if (nR == 2)
    {
        Determinent = ((values[0][0])*(values[1][1])) - ((values[1][0])*(values[0][1]));
        return Determinent;
    }
    else
    {
        for (indexcolomns = 0; indexcolomns<nC; indexcolomns++)
        {
            minorrows = 0;
            minorcolomns = 0;
            for (int i = 1; i<nR; i++)
            {
                for (int j = 0; j<nC; j++)
                {
                    if (j == indexcolomns)
                    {
                        continue;
                    }
                    minorMatrix.values[minorrows][minorcolomns] = values[i][j];
                    minorcolomns++;
                    if (minorcolomns == nC - 1)
                    {
                        minorrows++;
                        minorcolomns = 0;
                    }
                }
            }
            Determinent += values[0][indexcolomns] * pow(-1, indexcolomns)*minorMatrix.determinent();
        }
        return Determinent;
    }

}

CMatrix CMatrix::transpose()
{
    CMatrix temp(nR, nC);

    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            temp.values[i][j] = values[j][i];
            temp.values[j][i] = values[i][j];
        }
    }
    return temp;
}

CMatrix CMatrix::divElement(double x){
    CMatrix temp(nR, nC);
    for (int i = 0; i < nR; i++)
    {
        for (int t = 0; t < nC; t++)
        {
            temp.values[i][t] = x / values[i][t];
        }
    }
    return temp;
}

CMatrix CMatrix::multElement(double x) {

    CMatrix temp(nR, nC);

    for (int i = 0; i < nR; i++)
    {
        for (int t = 0; t < nC; t++)
        {
            temp.values[i][t] = x * values[i][t];
        }
    }

    return temp;
}

CMatrix CMatrix::getInverse()
{
    CMatrix MatrixInverse(nR,nC);

    // Created to get the determinant
    CMatrix matrixB(nR,nC);
    matrixB.copy(*this);

    double Determinant = matrixB.determinent();
    double Reciprocal = 1.0 / Determinant;
    // Used to get the n - 1 x n -1 matrices for to get inverse
    CMatrix Cofactors(nR - 1, nC - 1);

    int indexcols, indexrows, minorrows, minorcols, i, j;
    // z is indexrows for inverse matrix , y for indexcols for inverse matrix , powerindexes to adjust signs
    int z = 0, y = 0, powerindex1 = 0, powerindex2 = 0;

    if (nR == 2)
    {
        double temp = this->values[0][0];
        MatrixInverse.values[0][0] = MatrixInverse.values[1][1];
        MatrixInverse.values[1][1] = temp;

        MatrixInverse.values[1][0] = -MatrixInverse.values[1][0];
        MatrixInverse.values[0][1] = -MatrixInverse.values[0][1];

        for (i = 0; i < nR; i++)
        {
            for (j = 0; j < nC; j++)
            {
                MatrixInverse.values[i][j] = Reciprocal * MatrixInverse.values[i][j];
            }
        }
    }
    else
    {
        for (indexcols = 0, indexrows = 0; indexrows < nR; indexcols++)
        {
            minorrows = 0;
            minorcols = 0;
            if (indexrows == 0)
            {
                i = 1;
            }
            else
            {
                i = 0;
            }
            for (i; i < nR; i++)
            {
                if (i == indexrows)
                {
                    continue;
                }
                for (j = 0; j < nC; j++)
                {
                    if (j == indexcols)
                    {
                        continue;
                    }
                    Cofactors.values[minorrows][minorcols] = this->values[i][j];
                    minorcols++;
                    if (minorcols == nC - 1)
                    {
                        minorrows++;
                        minorcols = 0;
                    }
                }
            }
            MatrixInverse.values[z][y] = Cofactors.determinent() * pow(-1, powerindex1);
            powerindex2++;
            if (powerindex2 == nC)
            {
                powerindex2 = 0;
                powerindex1++;
            }
            powerindex1++;
            y++;
            if (y == nC)
            {
                z++;
                if (z == nR)
                {
                    z = nR - 1;
                }
                y = 0;
            }

            if (indexcols == nC - 1)
            {
                indexcols = -1;
                indexrows++;
            }
        }

    }
    MatrixInverse = MatrixInverse.transpose();
    for (int x = 0; x < nR; x++)
    {
        for (int y = 0; y < nC; y++)
        {
            MatrixInverse.values[x][y] = Reciprocal * MatrixInverse.values[x][y];
        }
    }
    return MatrixInverse;
}

CMatrix CMatrix::GaussianInverse()
{
    // Used for testing
    /*
	values[0][0] = 6; values[0][1] = 9; values[0][2] = 8; values[0][3] = 5; values[0][4] = 4;
	values[1][0] = 7; values[1][1] = 12; values[1][2] = 11; values[1][3] = 13; values[1][4] = 10;
	values[2][0] = 14; values[2][1] = 3; values[2][2] = 15; values[2][3] = 16; values[2][4] = 17;
	values[3][0] = 18; values[3][1] = 19; values[3][2] = 20; values[3][3] = 21; values[3][4] = 22;
	values[4][0] = 23; values[4][1] = 24; values[4][2] = 25; values[4][3] = 26; values[4][4] = 27;
    */
    //The New Matrix that will held the operations
    CMatrix gaussianMatrix(nR, nC * 2);
    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            gaussianMatrix.values[i][j] = values[i][j];
        }
    }
    for (int i = 0; i < nR; i++)
    {
        for (int j = nC; j < nC * 2; j++)
        {
            if ((j - i) == nC)
            {
                gaussianMatrix.values[i][j] = 1;
            }
        }
    }
    //this->display();
    //gaussianMatrix.display();
    //
    int IndexRows = 0, Index1 = 0;
    int factorrows = 1, factorcols = 0;
    int j = 0, k = 0, temp = 0,Row=0;
    double factor0 = 0,factor1 = 0;
    for (int i = 0; i < nR; i++)
    {
        for (j = 0; j < nR; j++)
        {
            if (j == 0)
            {
                factor1 = gaussianMatrix.values[Index1][Index1];
                for (k = 0; k < nC + nC; k++)
                {
                    gaussianMatrix.values[temp][k] /= factor1;
                }
                Index1++;
                //gaussianMatrix.display();
            }
            else
            {
                if (i > 0 && j == 1)
                {
                    Row = 0;
                }
                if (Row == IndexRows)
                {
                    Row++;
                    factorrows++;
                }
                factor0 = gaussianMatrix.values[factorrows][factorcols];
                for (k = 0; k < nC + nC; k++)
                {
                    gaussianMatrix.values[Row][k] -= factor0 * gaussianMatrix.values[IndexRows][k];
                }
                factorrows++;
                //gaussianMatrix.display();
            }
            Row++;
            if (factorrows == nR)
            {
                factorrows = 0;
                factorcols++;
                temp++;
            }
        }
        IndexRows++;
    }

    CMatrix inverseMatrix(nR, nC);
    for (int i = 0; i < nR; i++)
    {
        for (int j = 0; j < nC; j++)
        {
            inverseMatrix.values[i][j] = gaussianMatrix.values[i][j + nC];
        }
    }
//	gaussianMatrix.display();
//	inverseMatrix.display();
    return inverseMatrix;
}

CMatrix CMatrix::operator+(const CMatrix & x){

    return (this->add(x));

}

CMatrix CMatrix::operator-(const CMatrix& x){

    return (this->sub(x));

}

CMatrix CMatrix::operator*(const CMatrix &x)
{
    return (this->mult(x));
}

CMatrix  CMatrix::operator/(CMatrix& x)
{
    if (nR != x.nC)
    {
        throw "There is no unique solution\n";
    }
    CMatrix xInverse(x.nR,x.nC);
    xInverse = x.GaussianInverse();
    return (*this * xInverse);
}