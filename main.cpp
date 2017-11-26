#include <iostream>
using namespace std;

#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "cMatrix.h"

CMatrix find_Matrix(CMatrix *temp_matrices, char name, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (name == temp_matrices[i].getname())
        {
            // cout << "dsdfsdjkh" << endl;
            return temp_matrices[i];
        }
    }
}


bool isMatExist(string matStr, char name, int n)
{
    for (int i = 0; i < n; i++)
    {
        //cout<< "name is: "<< matStr[i] << endl;

        if (name == matStr[i])
        {
            //cout << "mat found" << endl;
            return true;
        }
    }
    return false;
}

int main()
{

    string matArr[] = {"A = [1 2 3;4 5 6;7 8 9]",
                       "B = [3 4 9;4 8 6;8 5 3]", "C = A - B"};

    CMatrix *temp_matrices;
    string matStr = "";
    char operation = 'a';
    temp_matrices = new CMatrix[10];
    int n = 0, j = 3;

    while (n < 3)
    {

        for (int i = 0; i < matArr[n].length(); i++)
        {

            if (((int)matArr[n][i] > 96 && (int)matArr[n][i] < 123) || ((int)matArr[n][i] > 64 && (int)matArr[n][i] < 91))
            {

                if (isMatExist(matStr, matArr[n][i], n) == false)
                {

                    temp_matrices[n].setname(matArr[n][i]);
                    matStr += matArr[n][i];
                }
            }
            else if (matArr[n][i] == '[')
            {

                temp_matrices[n] = CMatrix(matArr[n].substr(i + 1, matArr[n].find(']') - i - 1));
                temp_matrices[n].setname(matStr[n]);
                //temp_matrices[n].display();
                break;
            }
            else if (matArr[n][i] == '+' || matArr[n][i] == '-' || matArr[n][i] == '*' || matArr[n][i] == '/' || matArr[n][i] == '\'')
            {
                operation = matArr[n][i];

                // cout << operation << endl;
            }

            else if (matArr[n][i] == ' ')
            {
                continue;
            }
        }
        n++;
    }


    switch (operation)
    {

        case '+':

            CMatrix matA = find_Matrix(temp_matrices, matStr[0], j);
            matA.display();
            // //matMap[matStr[0]] = matMap[matStr[1]] + matMap[matStr[2]];
            CMatrix matC = find_Matrix(temp_matrices,matStr[2],j);
            // //CMatrix matA = temp_matrices[0];
            // //find_Matrix(temp_matrices,'A',j);
            CMatrix matB = find_Matrix(temp_matrices,matStr[1],j);
            matB.display();
            // //CMatrix matB = temp_matrices[1];
            // //CMatrix matC = temp_matrices[2];

            // //cout << matA.getname() << " -- " << matA.getCols() << " -- " << matA.getRows() << endl;
            // //cout << matB.getname() << " -- " << matB.getCols() << " -- " << matB.getRows() << endl;

            matC = matA + matB;
            matC.display();
            // cout << matC.getname() << " -- " << matC.getCols() << " -- " << matC.getRows() << endl;

            break;
            /*
            case '-':
    //             find_Matrix(temp_matrices,matStr[0],n) =find_Matrix(temp_matrices,matStr[1],n) - find_Matrix(temp_matrices,matStr[2],n);
                break;
            case '*':
    //             find_Matrix(temp_matrices,matStr[0],n) =find_Matrix(temp_matrices,matStr[1],n) * find_Matrix(temp_matrices,matStr[2],n);
                break;
            case '/':
                break;
            case '\'':
                break;
                */
    }

    // system("pause");
    return 0;
}
