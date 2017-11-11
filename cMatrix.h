#include <iostream>
using namespace std;

#ifndef CMATRIX
#define CMATRIX

//#include "cMatrix.cpp"
class CMatrix
{
int nR, nC;
double** values;
public:
CMatrix();
~CMatrix();
CMatrix(int nR, int nC, double first, ...);
CMatrix(CMatrix &x);
CMatrix(int nR, int nC);
CMatrix transpose();
void reset();
CMatrix(int nR, int nC,int hamada, double initVal);
void display();
void copy(CMatrix &x);
void add(CMatrix &x);
void sub(CMatrix &x);
void mult(CMatrix &x);
CMatrix coMatrix(int r,int c);
CMatrix operator=(CMatrix &x);
CMatrix operator=(double x);
CMatrix operator+=(CMatrix &x);
CMatrix operator+=(double x);
CMatrix operator+(double x);

CMatrix operator+(CMatrix &x);
CMatrix operator++ ();
CMatrix operator++ (int);

//CMatrix operator-(CMatrix &x);
CMatrix operator-=(CMatrix &x);
CMatrix operator-=(double x);
CMatrix operator-(double x);
CMatrix operator-(CMatrix& x);
CMatrix operator-- ();
CMatrix operator-- (int);
CMatrix operator*(CMatrix &x);
CMatrix operator*=(CMatrix &x);
CMatrix operator*=(double x);
};

#endif

