#include "stdio.h"
#include "stdlib.h"

#include "Graph.h"
#include "Solve.h"
#include "ErrorCodes.h"
#include "Tests.h"


int main(void)
{
    int errorCode = test();
    if (errorCode != ok)
    {
        printf("ERROR, CASE %d\n", errorCode);
        return errorCode;
    }
    printf("No errors!\n");
    return ok;
}