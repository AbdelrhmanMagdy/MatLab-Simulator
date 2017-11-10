#include <iostream> 
#include "cMatrix.h"
using namespace std;




int main()
{

    CMatrix x(3, 3, 1.2, 33.1, 5.11, 22.22 ,55.2 ,1.2, 2.2, 3.2, 4.2);
    CMatrix y(2, 2, 1.2, 2.2, 3.2, 4.2);
    x.display();
    x.coMatrix(1,1);
    // try{x.mult(y);}
    // catch(const char* e){
    //     cout<<e<<endl;
    // }

    return 0;
}
