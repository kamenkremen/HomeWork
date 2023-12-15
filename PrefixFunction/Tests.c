#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Tests.h"
#include "ErrorCodes.h"
#include "Files.h"
#include "Strings.h"

static int finish(const char* const result, const int returnValue)
{
    free(result);
    return returnValue;
}

static int fileTest(void)
{
    char* result = readFile("test1.txt");
    if (result == NULL)
    {
        return 1;
    }
    if (strcmp(result, "test1") != 0)
    {
        return finish(result, 2);
    }
    free(result);
    result = readFile("test2.txt");
    if (result == NULL)
    {
        return 3;
    }
    if (strcmp(result, "") != 0)
    {
        return finish(result, 4);
    }
    free(result);
    result = readFile("test3.txt");
    if (result == NULL)
    {
        return 5;
    }
    if (strcmp(result, "t\te\nst 3") != 0)
    {
        return finish(result, 6);
    }
    return finish(result, ok);
}

static int findSubStringTest(void)
{
    int errorCode = ok;
    int result = findSubString("test", "st", &errorCode);
    if (errorCode != ok || result != 2)
    {
        return 1;
    }
    result = findSubString("test", "a", &errorCode);
    if (errorCode != ok || result != -1)
    {
        return 2;
    }
    result = findSubString("testtesttesttest", "test", &errorCode);
    if (errorCode != ok || result != 0)
    {
        return 3;
    }
    return ok;
}

bool test(void)
{
    int errorCode = fileTest();
    bool isError = false;
    if (errorCode != ok)
    {
        isError = true;
        printf("ERROR IN FILE TEST, CASE %d\n", errorCode);
    }
    errorCode = findSubStringTest();
    if (errorCode != ok)
    {
        isError = true;
        printf("ERROR IN FIND SUB STRING TEST, CASE %d\n", errorCode);
    }
    return isError;
}
