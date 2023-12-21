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

static bool fileTestCase(const char* const fileName, const char* const neededResult)
{
    char* result = readFile(fileName);
    if (result == NULL)
    {
        return true;
    }
    if (strcmp(result, neededResult) != 0)
    {
        return (bool)finish(result, 1);
    }
    free(result);
    return false;
}

static int fileTest(void)
{
    if (fileTestCase("test1.txt", "test1"))
    {
        return 1;
    }
    if (fileTestCase("test2.txt", ""))
    {
        return 2;
    }
    if (fileTestCase("test3.txt", "t\te\nst 3"))
    {
        return 2;
    }
    return ok;
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
