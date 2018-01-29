#include <iostream>
using namespace std;

#include "Matlab.h"


int main(int argc, char *argv[]) {

    // if (argc > 1){
    //     openFile(argv[1]);
    // }
    // else {
    //     cline();
    // }

        CMatrix x(1,1,4,-9);
        CMatrix y(1,1,4,1);
        try{
        y = Log(x);
        y.display();
        }
        catch(const char *error){
            cout<<error<<endl;
        }
    // string s;
    // CMatrix hi(2,2,4,3);
    // hi.display();
    // hi.setName('A');
    // CMatrix bi(2,2,4,2);
    // bi.setName('B');
    // s = "(A./2)";
    // temp_matrices[0]=hi;
    // temp_matrices[1]=bi;
    // CMatrix zi;
    // zi = hi*2;
    // zi.display();
    // CMatrix x;
    // string y = InfixToPostfix(s);
    // std::cout << y<<endl;
    // x = EvaluatePostfix(InfixToPostfix(s));
    // x.display();
    return 0;
}