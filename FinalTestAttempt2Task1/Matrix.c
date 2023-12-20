#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Matrix.h"
#include "MyContainers.h"
#include "ErrorCodes.h"

struct Matrix
{
    int** array;
    size_t columns;
    size_t lines;
};

Matrix* createMatrix(void)
{
    Matrix* matrix = (Matrix*)calloc(1, sizeof(Matrix));
    return matrix;
}

matrixErrorCode input(Matrix* const matrix)
{
    if (matrix == NULL)
    {
        return nullPointerError;
    }
    for (size_t i = 0; i < matrix->lines; ++i)
    {
        free(matrix->array[i]);
    }
    free(matrix->array);
    printf("Enter the number of lines in the matrix:\n");
    if (scanf_s("%zu", &(matrix->lines)) != 1)
    {
        return inputError;
    }
    printf("Enter the number of columns in the matrix:\n");
    if (scanf_s("%zu", &(matrix->columns)) != 1)
    {
        return inputError;
    }
    printf("Enter the matrix:\n");
    matrix->array = (int**)calloc(matrix->lines, sizeof(int*));
    if (matrix->array == NULL)
    {
        return memoryError;
    }
    for (size_t i = 0; i < matrix->lines; ++i)
    {
        matrix->array[i] = (int*)calloc(matrix->columns, sizeof(int));
        if (matrix->array[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix->array[j]);
            }
            free(matrix->array);
            return memoryError;
        }
    }
    for (size_t line = 0; line < matrix->lines; ++line)
    {
        for (size_t column = 0; column < matrix->columns; ++column)
        {
            int element = 0;
            if (scanf_s("%d", &element) != 1)
            {
                for (size_t i = 0; i < matrix->lines; ++i)
                {
                    free(matrix->array[i]);
                }
                free(matrix->array);
                return inputError;
            }
            matrix->array[line][column] = element;
        }
    }
    return ok;
}

Pair** findSaddlePoints(const Matrix* const matrix, size_t* const size, matrixErrorCode* const errorCode)
{
    if (matrix == NULL)
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    Pair** saddlePoints = (Pair**)calloc(matrix->columns * matrix->lines, sizeof(Pair*));
    if (saddlePoints == NULL)
    {
        *errorCode = memoryError;
        return NULL;
    }
    size_t currentIndex = 0;
    for (size_t i = 0; i < matrix->lines; ++i)
    {
        int minimum = matrix->array[i][0];
        for (size_t j = 0; j < matrix->columns; ++j)
        {
            if (matrix->array[i][j] < minimum)
            {
                minimum = matrix->array[i][j];
            }
        }
        for (size_t minimumIndex = 0; minimumIndex < matrix->columns; ++minimumIndex)
        {
            if (matrix->array[i][minimumIndex] != minimum)
            {
                continue;
            }
            bool isSaddle = true;
            for (size_t j = 0; j < matrix->lines; ++j)
            {
                if (matrix->array[j][minimumIndex] > matrix->array[i][minimumIndex])
                {
                    isSaddle = false;
                    break;
                }
            }
            if (isSaddle)
            {
                Pair* pair = createPair();
                saddlePoints[currentIndex] = pair;

                if (saddlePoints[currentIndex] == NULL)
                {
                    for (size_t j = 0; j < matrix->lines * matrix->columns; ++j)
                    {
                        deletePair(saddlePoints[j]);
                    }
                    free(saddlePoints);
                    *errorCode = memoryError;
                    return NULL;
                }
                setFirst(saddlePoints[currentIndex], i);
                setSecond(saddlePoints[currentIndex], minimumIndex);
                ++currentIndex;
            }
        }
    }
    *size = currentIndex;
    return saddlePoints;
}

matrixErrorCode printSaddlePoints(const Matrix* const matrix)
{
    if (matrix == NULL)
    {
        return nullPointerError;
    }
    matrixErrorCode errorCode = ok;
    size_t size = 0;
    Pair** saddlePoints = findSaddlePoints(matrix, &size, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }
    if (size == 0)
    {
        printf("There is no saddle points!\n");
        free(saddlePoints);
        return ok;
    }
    printf("Saddle points:\n");
    for (size_t i = 0; i < size; ++i)
    {
        printf("line: %zu, column: %zu\n", getFirst(saddlePoints[i], &errorCode), getSecond(saddlePoints[i], &errorCode));
        deletePair(&saddlePoints[i]);
    }
    free(saddlePoints);
    return ok;
}

void deleteMatrix(Matrix** const matrix)
{
    for (size_t i = 0; i < (*matrix)->lines; ++i)
    {
        free((*matrix)->array[i]);
    }
    free((*matrix)->array);
    free(*matrix);
}

matrixErrorCode setMatrix(Matrix* const matrix, const size_t lines, const size_t columns, const char* const elements)
{
    if (matrix == NULL)
    {
        return nullPointerError;
    }
    if (strlen(elements) != lines * columns)
    {
        return inputError;
    }
    for (size_t i = 0; i < matrix->lines; ++i)
    {
        free(matrix->array[i]);
    }
    free(matrix->array);
    matrix->lines = lines;
    matrix->columns = columns;
    matrix->array = (int**)calloc(matrix->lines, sizeof(int*));
    if (matrix->array == NULL)
    {
        return memoryError;
    }
    for (size_t i = 0; i < matrix->lines; ++i)
    {
        matrix->array[i] = (int*)calloc(matrix->columns, sizeof(int));
        if (matrix->array[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(matrix->array[j]);
            }
            free(matrix->array);
            return memoryError;
        }
    }
    for (size_t i = 0; i < matrix->lines; ++i)
    {
        for (size_t j = 0; j < matrix->columns; ++j)
        {
            matrix->array[i][j] = elements[i * matrix->columns + j] - '0';
        }
    }
    return ok;
}

matrixErrorCode setElement(Matrix* const matrix, const size_t line, const size_t column, const int element)
{
    if (line >= matrix->lines || column >= matrix->columns)
    {
        return inputError;
    }
    matrix->array[line][column] = element;
    return ok;
}
