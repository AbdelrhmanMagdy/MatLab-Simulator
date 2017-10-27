#include "cMatrix.h"
using namespace std;

CMatrix::CMatrix(){
    nR = nC = 0;
    values = NULL;
}
CMatrix::CMatrix(string s){
    nR = nC =0;
    values = NULL;
    copy(s);
}
CMatrix::copy(string s){
    reset();
    
}
CMatrix::reset(){
    if (values){
        for (int i=0; i<nR; i++) delete[] values[i];
        delete[] vlaues;
    }
    nR = nC = 0;
    values = NULL;
}