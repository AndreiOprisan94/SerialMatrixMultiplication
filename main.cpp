#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "utils.h"

using namespace std;

static const char* const RESULT_PATH_ENV_NAME = "PPC_SERIAL_RESULT_PATH";

static int** multiplyMatrix(int** lhs, int** rhs, int matrixDimension);

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Please provide the matrix dimension";
        return -1;
    }

    int matrixDimension = atoi(argv[1]);

    cout << "[Serial] Matrix multiplication with square matrix of dimension:  " << matrixDimension << endl << flush;

    int **firstMatrix;
    int **secondMatrix;
    int **matrixMultiplicationResult;

    firstMatrix = allocateMatrix(matrixDimension);
    secondMatrix = allocateMatrix(matrixDimension);

    populateMatrixWithOnes(firstMatrix, matrixDimension);
    populateMatrixWithOnes(secondMatrix, matrixDimension);

    matrixMultiplicationResult = multiplyMatrix(firstMatrix, secondMatrix, matrixDimension);

    const auto resultPath = getenv(RESULT_PATH_ENV_NAME);
    ofstream destination(resultPath);

    cout << "Saving serial computation results to: " << resultPath << endl << flush;
    printMatrix(destination, matrixMultiplicationResult, matrixDimension);
    destination.close();

    freeMatrix(firstMatrix, matrixDimension);
    freeMatrix(secondMatrix, matrixDimension);
    freeMatrix(matrixMultiplicationResult, matrixDimension);

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