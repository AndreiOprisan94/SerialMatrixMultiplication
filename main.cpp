#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "utils.h"

using namespace std;

static int** multiplyMatrix(int** lhs, int** rhs, int matrixDimension);

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Please provide the matrix dimension";
        return -1;
    }

    int matrixDimension = atoi(argv[1]);

    const clock_t begin = clock();

    cout << "[Serial] Matrix multiplication with square matrix of dimension:  " << matrixDimension << endl << flush;

    int **firstMatrix;
    int **secondMatrix;
    int **matrixMultiplicationResult;

    firstMatrix = allocateMatrix(matrixDimension);
    secondMatrix = allocateMatrix(matrixDimension);

    populateMatrixWithOnes(firstMatrix, matrixDimension);
    populateMatrixWithOnes(secondMatrix, matrixDimension);

    matrixMultiplicationResult = multiplyMatrix(firstMatrix, secondMatrix, matrixDimension);

    freeMatrix(firstMatrix, matrixDimension);
    freeMatrix(secondMatrix, matrixDimension);
    freeMatrix(matrixMultiplicationResult, matrixDimension);

    const clock_t end = clock();
    const double timeSpent = ((double) end - begin) / CLOCKS_PER_SEC;
    printf("[SERIAL] Time=%f&MatrixSize=%d", timeSpent, matrixDimension);
    fflush(stdout);

    return 0;
}

static int** multiplyMatrix(int** lhs, int** rhs, int matrixDimension) {
    int** resultMatrix = allocateMatrix(matrixDimension);

    for (int i = 0; i < matrixDimension; i++) {
        for (int j = 0; j < matrixDimension; j++) {
            int result = 0;
            for (int k = 0; k < matrixDimension; ++k) {
                result += lhs[i][k] * rhs[k][j];
            }
            resultMatrix[i][j] = result;
        }
    }

    return resultMatrix;
}