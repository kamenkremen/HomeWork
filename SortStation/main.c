#include <stdio.h>
#include <stdlib.h>

#include "SortStation.h"
#include "ErrorCodes.h"
#include "Tests.h"
#include "Strings.h"

#define FAILED_TESTS 1

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return FAILED_TESTS;
    }
    printf("Enter the expression:\n");
    const char* const expression = readLine();
    if (expression == NULL)
    {
        printf("INPUT ERROR\n");
        return inputError;
    }
    char* result = sortStation(expression);
    if (result == NULL)
    {
        printf("CALCULATION ERROR\n");
        free(expression);
        return sortingStationError;
    }
    free(expression);
    printf("Expression in postfix form: %s\n", result);
    free(result);
    return ok;
}
