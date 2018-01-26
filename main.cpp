#include <iostream>
using namespace std;

#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "cMatrix.h"
#include <fstream>


string findMatrix(CMatrix *temp_matrices, char name, int n){

    for (int i = 0; i < n; i++) {

        if (temp_matrices[i].getName() == name)
            return to_string(i);
    }

    return  "";
}


int main(int argc, char *argv[]) {


    CMatrix temp_matrices[10];
    string matStr = "";
    char operation = 'a';
    int n = 0, matNo = 0;
    bool newMat = false;
    string matrixStr = "";
    string constNo = "";

    ifstream fileData("/Users/mamdouhelnakeeb/Desktop/ASU/CSE/3rd/Software Engineering/Project/Repo/Math_Library/bigexample2.m");
//    ifstream fileData(argv[1]);

    string fileLine;

    while (getline(fileData, fileLine)){

        for (int i = 0; i < fileLine.length(); i++){

            newMat = false;

            if (((int) fileLine[i] > 96 && (int) fileLine[i] < 123) || ((int) fileLine[i] > 64 && (int) fileLine[i] < 91)){

                if (findMatrix(temp_matrices, fileLine[i], matNo).empty()){

                    CMatrix tempMat;
                    tempMat.setName(fileLine[i]);
                    temp_matrices[matNo] = tempMat;

                    operation = 'a';

                    matNo++;

                }

                matStr += fileLine[i];

            }
            else if (fileLine[i] == '['){

                newMat = true;

                operation = 'a';

                i++;

                while (fileLine[i] != ']'){
                    matrixStr += fileLine[i];
                    i++;

                    if(i >= fileLine.length()){
                        getline(fileData, fileLine);
                        i = 0;
                    }
                }

                if (matrixStr[matrixStr.length() - 1] == ';'){
                    matrixStr = matrixStr.substr(0, matrixStr.length() - 1);
                }
                else if (matrixStr[matrixStr.length() - 2] == ';'){
                    matrixStr = matrixStr.substr(0, matrixStr.length() - 2);
                }

                temp_matrices[matNo - 1].setValues(matrixStr);
                matrixStr = "";
                break;

            }
            else if (fileLine[i] == '+' || fileLine[i] == '-' || fileLine[i] == '*' || fileLine[i] == '/' || fileLine[i] == '\''){

                operation = fileLine[i];

                if (fileLine[i] == '/' && fileLine[i - 1] == '.'){
                    operation = 'd';
                }
                else if (fileLine[i] == '*' && fileLine[i - 1] == '.'){
                    operation = 'm';
                }
            }

            else if (fileLine[i] == ' ' || fileLine[i] == '\r' || fileLine[i] == '\n' || fileLine[i] == '='){
                continue;
            }
            else if ((int) fileLine[i] > 47 && (int) fileLine[i] < 58){

                while (fileLine[i] != ' '){
                    constNo += fileLine[i];
                    i++;
                }

            }
//            else if (fileLine[i] == ']'){
//
//                if (matrixStr[matrixStr.length() - 1] == ';' || matrixStr[matrixStr.length() - 1] == ']'){
//                    matrixStr = matrixStr.substr(0, matrixStr.length() - 1);
//                }
//
//                temp_matrices[matNo - 1].setValues(matrixStr);
//                matrixStr = "";
//                newMat = false;
//            }
//            else {
//                if (newMat){
//
//                    matrixStr += fileLine[i];
////                    cout << fileLine.substr(i, fileLine.length() - i - 1) << endl;
//
////                    break;
//
//                }
////                temp_matrices[matNo - 1].setValues(fileLine.substr(i, fileLine.find(']') - i));
//            }

        }

        if (matStr.length() == 1 && !newMat){
            operation = 'p';
        }

        if (operation != 'a'){

            CMatrix mat1, mat2, mat3;
            int matIndex = 0;

            switch (operation){

                case '+':

                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];
                    mat2 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[2], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat3 = temp_matrices[matIndex];

                    mat3 = mat1 + mat2;

                    mat3.setName(temp_matrices[matIndex].getName());


                    cout << mat3.getName() << " = " << endl;
                    mat3.display();

                    temp_matrices[matIndex] = mat3;

                    break;
                case '-':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];
                    mat2 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[2], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat3 = temp_matrices[matIndex];

                    mat3 = mat1 - mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    cout << mat3.getName() << " = " << endl;
                    mat3.display();
                    temp_matrices[matIndex] = mat3;

                    break;
                case '*':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];
                    mat2 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[2], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat3 = temp_matrices[matIndex];

                    mat3 = mat1 * mat2;

                    mat3.setName(temp_matrices[matIndex].getName());

                    cout << mat3.getName() << " = " << endl;
                    mat3.display();
                    temp_matrices[matIndex] = mat3;

                    break;
                case '/':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];
                    mat2 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[2], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat3 = temp_matrices[matIndex];

                    try {

                        mat3 = mat1 / mat2;

                        mat3.setName(temp_matrices[matIndex].getName());

                        cout << mat3.getName() << " = " << endl;
                        mat3.display();
                        temp_matrices[matIndex] = mat3;
                    }
                    catch (const char* msg){
                        cout << msg << endl;
                    }

                    break;

                case '\'':
                    try{
                        mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];

                        matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                        mat2 = temp_matrices[matIndex];
//                mat2.display();

                        mat2 = mat1.transpose();

                        mat2.setName(temp_matrices[matIndex].getName());

                        cout << mat2.getName() << " = " << endl;
                        mat2.display();
                        temp_matrices[matIndex] = mat2;
                    }
                    catch (string e){
                        cout << e << endl;
                    }


                    break;
                case 'd':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat2 = temp_matrices[matIndex];


                    //mat2 ./ mat1
                    mat2 = mat1.divElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

                    cout << mat2.getName() << " = " << endl;
                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'm':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat2 = temp_matrices[matIndex];

                    // implement here

                    //mat2 .* mat1
                    mat2 = mat1.multElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

                    cout << mat2.getName() << " = " << endl;
                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'p':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str())];

                    cout << mat1.getName() << " = " << endl;
                    mat1.display();

                    break;
            }



        }

        matStr = "";
        n++;
    }


    if (fileData.is_open()){
        fileData.close();
    }



    return 0;
}
