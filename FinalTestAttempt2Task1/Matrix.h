#pragma once

#include "MyContainers.h"
// matrix 
typedef struct Matrix Matrix;
// matrixes error codes
typedef int matrixErrorCode;
// input matrix from the console
matrixErrorCode input(Matrix* const matrix);
// returns the array of saddle points
Pair** findSaddlePoints(const Matrix* const matrix, size_t* const size, matrixErrorCode* const errorCode);
// prints all of the saddle points
matrixErrorCode printSaddlePoints(const Matrix* const matrix);
// returns matrix
Matrix* createMatrix(void);
// deletes matrix
void deleteMatrix(Matrix** const matrix);
// sets the value of the matrix(sets only value > 0)(i made it for tests only)
matrixErrorCode setMatrix(Matrix* const matrix, const size_t lines, const size_t columns, const char* const elements);
// sets one element of the matrix
matrixErrorCode setElement(Matrix* const matrix, const size_t line, const size_t column, const int element);
