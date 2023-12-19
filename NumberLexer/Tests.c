#include <stdio.h>

#include "Tests.h"
#include "Lexer.h"

static int testLexer(void)
{
    const char* const test1 = "1234";
    if (!isNumber(test1))
    {
        return 1;
    }
    const char* const test2 = "1234.2";
    if (!isNumber(test2))
    {
        return 2;
    }
    const char* const test3 = "1234.2E";
    if (isNumber(test3))
    {
        return 3;
    }
    const char* const test4 = "1234.E";
    if (isNumber(test4))
    {
        return 4;
    }
    const char* const test5 = "1234E";
    if (isNumber(test5))
    {
        return 5;
    }
    const char* const test6 = "1234E+5";
    if (!isNumber(test6))
    {
        return 6;
    }
    const char* const test7 = "1234.2E7";
    if (isNumber(test7))
    {
        return 7;
    }
    const char* const test8 = "1234.2+5";
    if (isNumber(test8))
    {
        return 8;
    }
    const char* const test9 = "1234.5E+6";
    if (!isNumber(test9))
    {
        return 9;
    }
    const char* const test10 = "1234.5E-6";
    if (!isNumber(test10))
    {
        return 10;
    }
    return 0;
}

int tests(void)
{
    const int errorCode = testLexer();
    if (errorCode != 0)
    {
        printf("ERROR IN LEXER TEST, CASE %d\n", errorCode);
    }
    return errorCode;
}
