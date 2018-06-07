#include <iostream>
#include <string>
#include <fstream>

using namespace std;

static const string RESULTS_FILE_NAME = "../results";

static int** allocateMatrix(int matrixDimension);
static void freeMatrix(int** matrix, int matrixDimension);
static void printMatrix(ofstream& destination, int** matrix, int matrixDimension);
static void populateMatrixWithOnes(int** matrix, int matrixDimension);
static int** multiplyMatrix(int** lhs, int** rhs, int matrixDimension);

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cerr << "Please provide the matrix dimension";
        return -1;
    }

    int matrixDimension = atoi(argv[1]);

    cout << "Matrix Dimension is " << matrixDimension;

    int **firstMatrix;
    int **secondMatrix;
    int **matrixMultiplicationResult;

    firstMatrix = allocateMatrix(matrixDimension);
    secondMatrix = allocateMatrix(matrixDimension);

    populateMatrixWithOnes(firstMatrix, matrixDimension);
    populateMatrixWithOnes(secondMatrix, matrixDimension);

    matrixMultiplicationResult = multiplyMatrix(firstMatrix, secondMatrix, matrixDimension);

    ofstream destination(RESULTS_FILE_NAME);
    printMatrix(destination, matrixMultiplicationResult, matrixDimension);
    destination.close();

    freeMatrix(firstMatrix, matrixDimension);
    freeMatrix(secondMatrix, matrixDimension);
    freeMatrix(matrixMultiplicationResult, matrixDimension);

    return 0;
}

static int** allocateMatrix(int matrixDimension) {
    int** matrix = new int*[matrixDimension];

    for (int i = 0; i < matrixDimension; i++) {
        matrix[i] = new int[matrixDimension];
    }

    return matrix;
}

static void freeMatrix(int** matrix, int matrixDimension) {
    for(int i = 0; i < matrixDimension; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

static void populateMatrixWithOnes(int** matrix, int matrixDimension) {
    for (int i = 0; i < matrixDimension; i++) {
        for (int j = 0; j < matrixDimension; ++j) {
            matrix[i][j] = 1;
        }
    }
}

static void printMatrix(ofstream& destination, int** matrix, int matrixDimension) {
    for (int i = 0; i < matrixDimension; ++i) {
        for (int j = 0; j < matrixDimension; ++j) {
            destination << matrix[i][j] << " ";
        }
        destination << endl;
    }
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