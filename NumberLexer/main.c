#include <stdlib.h>
#include <stdio.h>

#include "Lexer.h"
#include "Strings.h"

#define WRONG_TEST_ERROR_CODE 1;

int main(void)
{
    const int errorCode = tests();
    if (errorCode != 0)
    {
        return WRONG_TEST_ERROR_CODE;
    }
    printf("Enter the string:\n");
    char* string = readLine();
    bool result = isNumber(string);
    printf("%s\n", result ? "it is a number" : "it is not a number");
    free(string);
    return 0;
}
