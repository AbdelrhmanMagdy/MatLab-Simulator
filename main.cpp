#include <iostream>
using namespace std;

#include "Matlab.h"


int main(int argc, char *argv[]) {

    if (argc > 0){

//        openFile(argv[1]);
        openFile("../example/example2.m");
    }
    else {
        cline();
    }


    return 0;
}