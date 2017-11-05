#ifndef CMATRIX
#define CMATRIX
class CMatrix
{
int nR, nC;
double** values;
public:
CMatrix();
CMatrix(int nR, int nC, ...);
void reset();
void display();
};

#endif
