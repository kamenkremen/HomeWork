#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "PostfixCalculator.h"
#include "Stack.h"
#include "Tests.h"
#include "ErrorCodes.h"
#include "Strings.h"

char* ERRORNAMES[6] =
{
    "OK",
    "MEMORY ERROR",
    "NULL POINTER ERROR",
    "ZERO DIVISION ERROR",
    "INPUT ERROR",
    "STACK ERROR",
};

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    printf("Enter the string to calculate:\n");
    errorCode = 0;
    char* string = readLine(&errorCode);
    if (errorCode != ok)
    {
        printf("%s\n", ERRORNAMES[errorCode]);
        return errorCode;
    }
    int result = postfixCalculator(string, &errorCode);
    if (errorCode != ok)
    {
        printf("%s\n", ERRORNAMES[errorCode]);
        free(string);
        return errorCode;
    }
    printf("Result = %d\n", result);
    free(string);
    return ok;
}
