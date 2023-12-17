#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "CycleList.h"
#include "Solve.h"
#include "ErrorCodes.h"
#include "Tests.h"

static char* ERROR_NAMES[5] = {
    "OK",
    "MEMORY ERROR",
    "NULL POINTER ERROR",
    "SOLVING ERROR",
    "INPUT ERROR",
};

static int finish(const int errorCode)
{
    printf("%s\n", ERROR_NAMES[errorCode]);
    return 1;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode)
    {
        return errorCode;
    }
    size_t n = 0;
    size_t m = 0;
    printf("Enter the amount of warriors(n):\n");
    if (scanf_s("%zu", &n) != 1)
    {
        return finish(inputError);
    }
    printf("Enter the step in which warriors will be killed(m):\n");
    if (scanf_s("%zu", &m) != 1)
    {
        return finish(inputError);
    }
    errorCode = ok;
    const int result = getSurvivedStartedPosition(n, m, &errorCode);
    if (errorCode != ok)
    {
        return finish(errorCode);
    }
    printf("To not get killed, you should be on the %d position from the start\n", result);
    return ok;
}
