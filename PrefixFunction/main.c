#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Files.h"
#include "Strings.h"
#include "ErrorCodes.h"
#include "Tests.h"

static int finish(const char* const subString, const char* const fileName, const char* const file, const int returnValue)
{
    free(subString);
    free(file);
    free(fileName);
    return returnValue;
}

int main(void)
{
    if (test())
    {
        return 1;
    }
    int errorCode = ok;
    printf("Enter the substring:\n");
    char* subString = readLine();
    if (subString == NULL)
    {
        printf("INPUT ERROR\n");
        return inputError;
    }
    printf("Enter the name of file:\n");
    char* fileName = readLine();
    if (fileName == NULL)
    {
        printf("INPUT ERROR\n");
        return finish(subString, NULL, NULL, inputError);
    }
    char* file = readFile(fileName);
    if (file == NULL)
    {
        printf("FILE READING ERROR\n");
        return finish(subString, fileName, NULL, inputError);;
    }
    int index = findSubString(file, subString, &errorCode);
    if (errorCode != ok)
    {
        printf("FILE READING ERROR\n");
        return finish(subString, fileName, file, inputError);
    }
    if (index == -1)
    {
        printf("String doesn`t contain substring\n");
    }
    else
    {
        printf("String contain substring starting from index %d\n", index);
    }
    return finish(subString, fileName, file, ok);
}
