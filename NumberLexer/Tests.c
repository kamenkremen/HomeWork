#include <stdio.h>

#include "Tests.h"
#include "Lexer.h"

static int testLexer(void)
{
    const char* const testStrings[11] = { "1234", "1234.2", "1234.2E", "1234.E", "1234E", "1234E+5", "1234.2E7", "1234.2+5", "1234.5E+6", "1234.5E-6", ""};
    const bool* const testValues[11] = { true, true, false, false, false, true, false, false, true, true, false };
    for (size_t i = 0; i < 11; ++i)
    {
        if (isNumber(testStrings[i]) != testValues[i])
        {
            return i + 1;
        }
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
