#include <iostream> 
#include "cMatrix.h"
using namespace std;




int main()
{

CMatrix x(2,3, 1.0, 5.6 ,  3.66, 4.3, 6.2 ,10.55);
x.display();
CMatrix a(x);
a.display();
return 0;
}
