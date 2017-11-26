#include "stdarg.h"
#include "string.h"
#include "cMatrix.h"
#include "stdio.h"
#include <iostream>
#include <cmath>

using namespace std;

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
CMatrix::CMatrix(std::string matStr)
{
	nR = 0, nC = 0;

	for (int i = 0; i < matStr.length(); i++)
	{

		if (matStr[i] == ' ' && nR == 0)
		{
			nC++;
		}
		if (matStr[i] == ';')
		{
			nR++;
		}
	}

	nC++;
	nR++;

	std::string tempStr = matStr;

	values = new double *[nR];

	for (int i = 0; i < nR; i++)
	{
		values[i] = new double[nC];

		for (int j = 0; j < nC; j++)
		{
			char cutChar = 'a';

			if (j == nC - 1)
			{
				cutChar = ';';
			}
			else
			{

				cutChar = ' ';
			}

			values[i][j] = atof(tempStr.substr(0, tempStr.find(cutChar)).c_str());
			tempStr.erase(0, tempStr.find(cutChar) + 1);
		}
	}
}

void CMatrix::setname(char nme)
{
	this->nme = nme;
}

char CMatrix::getname()
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
			if (values[iR][iC] == -0)
			{
				values[iR][iC] = 0;
			}
            printf("%.4f\t",values[iR][iC]);
        }
        printf("\n\n");
    }
    printf("\n");
}


CMatrix CMatrix::add(const CMatrix & x){
    if (x.nR != nR || x.nC != nC)
	{
		throw("Invalid Matrix Addition columns and rows must be equal in the two matrices");
	}

	CMatrix temp(*this);

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
    if (x.nR != nR || x.nC != nC)
    {
        throw("Invalid Matrix Subtraction columns and rows must be equal in the two matrices");
    }
	CMatrix temp(*this);
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
	CMatrix gaussianMatrix(nR, nC + nC);
	for (int i = 0; i < nR; i++)
	{
		for (int j = 0; j < nC; j++)
		{
			gaussianMatrix.values[i][j] = values[i][j];
		}
	}
	for (int i = 0; i < nR; i++)
	{
		for (int j = nC; j < nC + nC; j++)
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
	//gaussianMatrix.display();
	//inverseMatrix.display();
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