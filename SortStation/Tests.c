#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SortStation.h"
#include "ErrorCodes.h"

static int finish(char* const string, const returnValue)
{
    free(string);
    return returnValue;
}

static int testSortStation(void)
{
    char* result = sortStation("(1 + 1) * 2");
    if (result == NULL || strcmp(result, "1 1 + 2 *") != 0)
    {
        return finish(result, 1);
    }
    free(result);
    result = sortStation("((1 + 1) * 2");
    if (result != NULL)
    {
        return finish(result, 2);
    }
    result = sortStation("(1 + 1)) * 2");
    if (result != NULL)
    {
        return finish(result, 3);
    }
    result = sortStation("(1 !+ 1) *! 2");
    if (result != NULL)
    {
        return finish(result, 4);
    }
    result = sortStation("(2 + 4) / 9 + 5");
    if (result == NULL || strcmp(result, "2 4 + 9 / 5 +") != 0)
    {
        printf("%s\n", result);
        return finish(result, 5);
    }
    return finish(result, ok);
}

int tests(void)
{
    const int errorCode = testSortStation();
    if (errorCode != ok)
    {
        printf("ERROR IN TESTING SORT STATION, CASE %d\n", errorCode);
    }
    return errorCode;
}
