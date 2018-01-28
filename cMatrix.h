#include <string>
#include <stdlib.h>

#ifndef CMATRIX
#define CMATRIX
class CMatrix
{
    int nR, nC;
    char nme;
    double** values;
public:

    enum MI
    {
        MI_ZEROS,
        MI_ONES,
        MI_EYE,
        MI_RAND,
        MI_VALUE
    };

    CMatrix();
    CMatrix(std::string matStr);
    CMatrix(const CMatrix &x);
    CMatrix(int nR, int nC);
    void reset();
    CMatrix(int nR, int nC, int initialization, double initializationValue);
    CMatrix find_Matrix(CMatrix *temp_matrices, char nme, int n);
    bool isMatExist(std::string matStr, char nme, int n);
    void setName(char nme);
    char getName();
    double **getValues();
    void addCol();
    void addRow();
    void setValues(std::string matStr);
    int getRows();
    int getCols();
    void display();
    void copy(const CMatrix &x);


    CMatrix add(const CMatrix & x);
    CMatrix sub(const CMatrix &x);
    CMatrix mult(const CMatrix &x);
    CMatrix divElement(double x);
    CMatrix multElement(double x);
    CMatrix coMatrix(int r,int c);
    double determinent();
    CMatrix getInverse();
    CMatrix transpose();
    CMatrix GaussianInverse();
    CMatrix operator+(const CMatrix &x);
    CMatrix operator-(const CMatrix& x);
    CMatrix operator*(const CMatrix &x);
    CMatrix operator/(CMatrix& x);

    CMatrix operator ^ (const int a) ;
    friend CMatrix PerformOperation(char operation, CMatrix operand1, CMatrix operand2);
    friend CMatrix Sin(const CMatrix &a);
    friend CMatrix Cos(const CMatrix &a);
    friend CMatrix Tan(const CMatrix &a);
    friend CMatrix Ln(const CMatrix &a);
    friend CMatrix Log(const CMatrix &a);
    friend CMatrix Sqrt(const CMatrix &a);

    friend CMatrix solve(CMatrix mat1, char op, CMatrix mat2);
    friend CMatrix solve(CMatrix mat1, char op);
};
CMatrix Rand(int nR, int nC);
CMatrix Eye(int nR, int nC);
CMatrix Zeros(int nR, int nC);
CMatrix Ones(int nR, int nC);

#endif
