#include <stdlib.h>
#include <stdio.h>

#include "Solve.h"
#include "ErrorCodes.h"

static int solveTest(void)
{
    int errorCode = solve(3, 5, "test1.txt", "test1out.txt");
    if (errorCode != ok)
    {
        return 1;
    }
    FILE* file = NULL;
    fopen_s(&file, "test1out.txt", "r");
    if (file == NULL)
    {
        return 1;
    }
    int number = 0;
    int answer1[9] = { 2, 1, 2, 5, 4, 3, 6, 7, 8 };
    for (size_t i = 0; i < 9; ++i)
    {
        if (fscanf_s(file, "%d", &number) != 1)
        {
            fclose(file);
            return 2;
        }
        if (number != answer1[i])
        {
            fclose(file);
            return 3;
        }
    }
    fclose(file);
    errorCode = solve(2, 2, "test2.txt", "test2out.txt");
    if (errorCode != ok)
    {
        return 4;
    }
    fopen_s(&file, "test2out.txt", "r");
    if (file == NULL)
    {
        return 5;
    }
    int answer2[7] = { 1, 2, 2, 3, 7, 4, 3 };
    for (size_t i = 0; i < 7; ++i)
    {
        if (fscanf_s(file, "%d", &number) != 1)
        {
            fclose(file);
            return 6;
        }
        if (number != answer2[i])
        {
            fclose(file);
            return 7;
        }
    }
    fclose(file);
    return ok;
}

int tests(void)
{
    int errorCode = solveTest();
    if (errorCode != ok)
    {
        printf("ERROR IN SOLVE TEST, CASE %d\n", errorCode);
    }
    return errorCode;
}
