#include <stdlib.h>
#include <stdio.h>

#include "Lexer.h"

#define WRONG_TEST_ERROR_CODE 1;

int main(void)
{
    const int errorCode = tests();
    if (errorCode != 0)
    {
        return WRONG_TEST_ERROR_CODE;
    }
    char* string = "1234.5E-678";
    bool result = isNumber(string);
    printf("%s\n", result ? "it is a number" : "it is not a number");
    return 0;
}
