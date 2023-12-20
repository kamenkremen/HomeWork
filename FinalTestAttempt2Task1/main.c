#include <stdlib.h>
#include <stdio.h>

#include "ErrorCodes.h"
#include "Matrix.h"
#include "Tests.h"

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return 1;
    }
    Matrix* matrix = createMatrix();
    if (matrix == NULL)
    {
        printf("MEMORY ERROR\n");
        return 1;
    }
    if (input(matrix) != ok)
    {
        printf("INPUT ERROR");
        deleteMatrix(&matrix);
        return 1;
    }
    if (printSaddlePoints(matrix) != ok)
    {
        printf("MEMORY ERROR\n");
        deleteMatrix(&matrix);
        return 1;
    }
    deleteMatrix(&matrix);
    return ok;
}
