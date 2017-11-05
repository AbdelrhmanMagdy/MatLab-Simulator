#ifndef CMATRIX
#define CMATRIX
class CMatrix
{
int nR, nC;
double** values;
public:
CMatrix();
~CMatrix();
CMatrix(int nR, int nC, ...);
CMatrix(CMatrix &x);
void reset();
void display();
void copy(CMatrix &x);
};

#endif
