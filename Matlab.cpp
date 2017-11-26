//
// Created by Mamdouh El Nakeeb on 11/26/17.
//

#include "Matlab.h"

std::string itos(int in){

    std::ostringstream stream;
    stream << in;
    return stream.str();
}

std::string findMatrix(CMatrix *temp_matrices, char name, int n){

    for (int i = 0; i < n; i++) {

        if (temp_matrices[i].getName() == name)
            return itos(i);
    }

    return  "";

}

void openFile(char* path) {

    CMatrix temp_matrices[10];
    std::string matStr = "";
    char operation = 'a';
    int n = 0, matNo = 0;
    bool newMat = false;
    std::string matrixStr = "";
    std::string constNo = "";

    std::ifstream fileData(path);

    std::string fileLine;

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

                        mat3.display();
                        temp_matrices[matIndex] = mat3;
                    }
                    catch ( const char* e){
                        printf("%s",e);
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

                        mat2.display();
                        temp_matrices[matIndex] = mat2;
                    }
                    catch (const char* e){
                        printf("%s",e);
                    }


                    break;
                case 'd':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat2 = temp_matrices[matIndex];


                    //mat2 ./ mat1
                    mat2 = mat1.divElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

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

                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'p':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str())];

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


}


void cline(){

    CMatrix temp_matrices[10];
    std::string matStr = "";
    char operation = 'a';
    int n = 0, matNo = 0;
    bool newMat = false;
    std::string matrixStr = "";
    std::string constNo = "";


    std::string fileLine;

    std::cout << "Type 'exit' when finished" << std::endl;

    while (getline(std::cin, fileLine)){

        if (fileLine == "exit"){
            break;
        }

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
                        getline(std::cin, fileLine);
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

                        mat3.display();
                        temp_matrices[matIndex] = mat3;
                    }
                    catch (const char* e){
                        printf("%s", e);
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

                        mat2.display();
                        temp_matrices[matIndex] = mat2;
                    }
                    catch (const char* e){
                        printf("%s", e);
                    }

                    break;
                case 'd':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[1], matNo).c_str())];

                    matIndex = atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str());
                    mat2 = temp_matrices[matIndex];


                    //mat2 ./ mat1
                    mat2 = mat1.divElement(atof(constNo.c_str()));

                    mat2.setName(temp_matrices[matIndex].getName());

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

                    mat2.display();

                    temp_matrices[matIndex] = mat2;
                    break;

                case 'p':
                    mat1 = temp_matrices[atoi(findMatrix(temp_matrices, matStr[0], matNo).c_str())];

                    mat1.display();

                    break;
            }

        }

        matStr = "";
        n++;
    }

}