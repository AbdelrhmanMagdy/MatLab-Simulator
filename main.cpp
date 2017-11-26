#include <iostream>
using namespace std;

#include "Matlab.h"


int main(int argc, char *argv[]) {

    if (argc > 1){

        openFile(argv[1]);
    }
    else {
        cline();
    }


    return 0;
}