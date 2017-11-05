#include <iostream> 
#include "cMatrix.h"
using namespace std;




int main()
{

    CMatrix x(2, 2, 1.2, 2.2, 3.2, 4.2);
    CMatrix y(2, 3,2.3,2.3, 1.2, 2.2, 3.2, 4.2);
    x.display();
    try{x.add(y);}
    catch(const char* e){
        cout<<"error: "<<e<<endl;
    }
    x.display();

    return 0;
}
