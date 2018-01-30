#include <iostream>
using namespace std;

#include "Matlab.h"
#include "cMatrix.h"


int main(int argc, char *argv[]) {

    if (argc > 1){
        openFile(argv[1]);
    }
    else {
        cline();
    }


//     CMatrix D = Ones(4, 4);
//     D.setName('D');
//     CMatrix C=Ones(4,4);
//     C.setName('C');
//     CMatrix X;
//     // X.setName('X');
//     temp_matrices[0]=D;
//     temp_matrices[1]=C;
//     string s = " ((C*D .+ 4)./2.0 + sqrt(D))*C";
//     // cout<<InfixToPostfix(s)<<endl;
//    X = Equation(s);//EvaluatePostfix(InfixToPostfix(s));
//         //    D.display();
//    X.display();



   // string s = " [1.2 2.3 2.5;[1.3 2.4;4.6 1.3],[3.2;7.8]]";
   // CMatrix x;
   // try{
   // x.subMatrixParser(s); //subMatrixParser(s);
   // x.display();
   // }
   // catch(const char* error){cout<<error;}
   // cout << subMatrixExist(s)<<endl;
   // CMatrix x(1,1,4,-9);
   // CMatrix y(1,1,4,1);
   // try{
   // y = Log(x);
   // y.display();
   // }
   // catch(const char *error){
   //     cout<<error<<endl;
   // }
   // string s;
   // CMatrix hi(2,2,4,3);
   // // hi.display();
   // hi.setName('A');
   // CMatrix bi(2,2,4,2);
   // bi.setName('B');
   // s = "((A./2)";
   // temp_matrices[0]=hi;
   // temp_matrices[1]=bi;
   // CMatrix zi;
   // // zi = hi*2;
   // // zi.display();
   // CMatrix x;
   // string y = InfixToPostfix(s);
   // std::cout << y<<endl;
   // x = EvaluatePostfix(InfixToPostfix(s));
   // x.display();
   return 0;
}