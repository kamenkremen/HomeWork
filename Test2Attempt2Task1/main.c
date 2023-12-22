#include <stdlib.h>
#include <stdio.h>

#include "ErrorCodes.h"
#include "Solve.h"
#include "Tests.h"

#define FAILED_TEST 1;

int main(void)
{

    int errorCode = tests();
    if (errorCode != ok) 
    {
        return FAILED_TEST;
    }
    int a = 0;
    int b = 0;
    printf("Enter a:\n");
    if (scanf_s("%d", &a) != 1)
    {
        printf("INPUT ERROR\n");
        return 1;
    }
    printf("Enter b:\n");
    if (scanf_s("%d", &b) != 1)
    {
        printf("INPUT ERROR\n");
        return 1;
    }
    errorCode = solve(a, b, "input.txt", "output.txt");
    if (errorCode != ok)
    {
        printf("ERROR %d IN SOLVING\n", errorCode);
        return 1;
    }
    printf("Succesfully executed!\n");

    return ok;
}
