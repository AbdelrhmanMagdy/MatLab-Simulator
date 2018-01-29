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
    CMatrix();

    enum MI
    {
        MI_ZEROS,
        MI_ONES,
        MI_EYE,
        MI_RAND,
        MI_VALUE
    };

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

    static CMatrix Log (const CMatrix & a ) ;
    CMatrix operator ^( const int a);

    CMatrix Sin(const CMatrix &a);
    CMatrix Cos(const CMatrix &a);
    CMatrix Tan(const CMatrix &a);

    void subMatrixParser(std::string matStr);

    void setSubMatrix(int r, int c, CMatrix& m);
    void addColumn(CMatrix& m);
    void addRow(CMatrix& m);
    void copy(std::string s);
    void copy(double d);
    CMatrix operator=(double d);
};

#endif
