#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "Stack.h"
#include "BracketBalance.h"
#include "Strings.h"
#include "ErrorCodes.h"
#include "Tests.h"


const char* const ERRORNAMES[4] = {
    "OK",
    "MEMORY ERROR",
    "INPUT ERROR",
    "NULL POINTER ERROR",
};

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    printf("Enter the brackets:\n");
    const char* string = readLine(&errorCode);
    if (errorCode != ok)
    {
        printf("%s\n", ERRORNAMES[errorCode]);
        return errorCode;
    }
    const int result = checkBalance(string);
    if (result > balanced)
    {
        printf("ERROR %d\n", result);
        free(string);
        return result;
    }
    printf("%s", result == balanced ? "Balanced\n" : "Not balanced\n");
    free(string);
    return ok;
}
