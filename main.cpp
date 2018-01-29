#include <iostream>
using namespace std;

#include "Matlab.h"
#include <string>

using namespace std;


int main(int argc, char *argv[]) {

    if (argc > 1){

        openFile(argv[1]);
    }
    else {
        cline();
    }

    /*CMatrix A(3,3);
    A.setValues("3 2 1;4 5 6;7 8 9");
    A.display();
    CMatrix B(2,1);
    B.setValues("3 3");
    B.display();

    A.setSubMatrix(1,2,B);
    A.display();*/

    /*CMatrix A(4,4);
    string x = "B = [3.4 5.7 4.2 1.4; 6.3 2.5 8.1 3.1; 6.4 2.8 7.1 8.1; 3.2 5.1 7.2 6.2]";
    A.copy(x);
    A.display();*/

    return 0;
}