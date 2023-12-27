#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Tests.h"
#include "Files.h"
#include "ErrorCodes.h"

static void freeData(char** const numbers, char** const names, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(numbers[i]);
        free(names[i]);
    }
}

static int readPhoneBookTest(void)
{
    char* numbers[100] = { 0 };
    char* names[100] = { 0 };
    size_t size = 0;
    readBook(numbers, names, &size, "test1.txt");
    if (size != 0)
    {
        freeData(numbers, names, size);
        return 1;
    }
    readBook(numbers, names, &size, "test2.txt");
    if (size != 2 || strcmp(numbers[0], "1") != 0 || strcmp(names[0], "test1") != 0 || strcmp(numbers[1], "2") != 0 || strcmp(names[1], "test2") != 0)
    {
        freeData(numbers, names, size);
        return 2;
    }
    freeData(numbers, names, size);
    return ok;
}

static int writePhoneBookTest(void)
{
    char* numbers[100] = { 0 };
    numbers[0] = "1";
    char* names[100] = { 0 };
    names[0] = "test1";
    size_t size = 0;
    size_t newRecordings = 1;
    FILE* file = NULL;
    fopen_s(&file, "writingTest1.txt", "w");
    fclose(file);
    if (writeBook(numbers, names, &size, "writingTest1.txt", &newRecordings) || newRecordings != 0 || size != 1)
    {
        return 1;
    }
    readBook(numbers, names, &size, "writingTest1.txt");
    if (size != 1 || strcmp(numbers[0], "1") != 0 || strcmp(names[0], "test1"))
    {
        freeData(numbers, names, size);
        return 2;
    }
    numbers[1] = "2";
    names[1] = "test2";
    newRecordings = 1;
    if (writeBook(numbers, names, &size, "writingTest1.txt", &newRecordings) || newRecordings != 0 || size != 2)
    {
        freeData(numbers, names, 1);
        return 3;
    }
    free(numbers[0]);
    free(names[0]);
    readBook(numbers, names, &size, "writingTest1.txt");
    if (newRecordings != 0 || size != 2 || strcmp(numbers[1], "2") != 0 || strcmp(names[1], "test2"))
    {
        freeData(numbers, names, size);
        return 4;
    }
    freeData(numbers, names, size);
    return ok;
}

bool tests(void)
{
    bool isError = false;
    int errorCode = readPhoneBookTest();
    if (errorCode != ok)
    {
        printf("ERROR IN READ TESTS, CASE %d\n", errorCode);
        isError = true;
    }
    errorCode = writePhoneBookTest();
    if (errorCode != ok)
    {
        printf("ERROR IN WRITE TESTS, CASE %d\n", errorCode);
        isError = true;
    }
    return isError;
}
