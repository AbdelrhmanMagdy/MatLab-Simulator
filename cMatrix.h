#ifndef CMATRIX
#define CMATRIX
class CMatrix
{
int nR, nC;
double** values;
public:
CMatrix();
~CMatrix();
CMatrix(int nR, int nC, double first, ...);
CMatrix(CMatrix &x);
CMatrix(int nR, int nC, double init);
CMatrix(int nR, int nC);
CMatrix transpose();
void reset();
void display();
void copy(CMatrix &x);
void add(CMatrix &x);
void sub(CMatrix &x);
};

#endif
