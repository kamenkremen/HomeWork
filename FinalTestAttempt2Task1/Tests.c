#include <stdlib.h>

#include "Matrix.h"
#include "ErrorCodes.h"
#include "MyContainers.h"

static int testMatrix(void)
{
    Matrix* matrix = createMatrix();
    if (matrix == NULL)
    {
        return 1;
    }
    if (setMatrix(matrix, 2, 3, "123132") != ok)
    {
        return 2;
    }
    size_t size = 0;
    int errorCode = ok;
    Pair** saddlePoints = findSaddlePoints(matrix, &size, &errorCode);
    if (errorCode != ok || size != 2)
    {
        for (size_t i = 0; i < size; ++i)
        {
            deletePair(&saddlePoints[i]);
        }
        free(saddlePoints);
        return 3;
    }
    if (getFirst(saddlePoints[0], &errorCode) != 0 || getSecond(saddlePoints[0], &errorCode) != 0 || errorCode != ok)
    {
        for (size_t i = 0; i < size; ++i)
        {
            deletePair(&saddlePoints[i]);
        }
        free(saddlePoints);
        return 4;
    }
    if (getFirst(saddlePoints[1], &errorCode) != 1 || getSecond(saddlePoints[1], &errorCode) != 0 || errorCode != ok)
    {
        for (size_t i = 0; i < size; ++i)
        {
            deletePair(&saddlePoints[i]);
        }
        free(saddlePoints);
        return 5;
    }
    for (size_t i = 0; i < size; ++i)
    {
        deletePair(&saddlePoints[i]);
    }
    free(saddlePoints);
    if (setElement(matrix, 0, 0, -1) != ok)
    {
        return 6;
    }
    saddlePoints = findSaddlePoints(matrix, &size, &errorCode);
    if (errorCode != ok || size != 1)
    {
        for (size_t i = 0; i < size; ++i)
        {
            deletePair(&saddlePoints[i]);
        }
        free(saddlePoints);
        return 7;
    }
    if (getFirst(saddlePoints[0], &errorCode) != 1 || getSecond(saddlePoints[0], &errorCode) != 0 || errorCode != ok)
    {
        for (size_t i = 0; i < size; ++i)
        {
            deletePair(&saddlePoints[i]);
        }
        free(saddlePoints);
        return 8;
    }
    for (size_t i = 0; i < size; ++i)
    {
        deletePair(&saddlePoints[i]);
    }
    free(saddlePoints);
    deleteMatrix(&matrix);
    return ok;
}

int tests(void)
{
    const int errorCode = testMatrix();
    if (errorCode != ok)
    {
        printf("ERROR IN TESTING MATRIX, CASE %d\n", errorCode);
    }
    return errorCode;
}
