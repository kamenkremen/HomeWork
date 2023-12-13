#include <stdlib.h>
#include <stdio.h>

#include "ErrorCodes.h"

size_t solve(size_t number)
{
    int digits[10] = { 0 };
    while (number > 0)
    {
        int digit = number % 10;
        number /= 10;
        ++digits[digit];
    }
    size_t result = 0;
    for (size_t i = 0; i < 10; ++i)
    {
        for (size_t j = 0; j < digits[i]; ++j)
        {
            result *= 10;
            result += i;
        }
    }
    return result;
}

int test(void)
{
    if (solve(54321) != 12345)
    {
        return 1;
    }
    if (solve(12345) != 12345)
    {
        return 2;
    }
    if (solve(5) != 5)
    {
        return 3;
    }
    if (solve(12345687) != 12345678)
    {
        return 4;
    }
    return ok;
}

int main(void)
{
    int errorCode = test();
    if (errorCode != ok)
    {
        printf("ERROR IN TESTS, CASE %d\n", errorCode);
        return errorCode;
    }
    int number = 0;
    printf("Enter the number: ");
    if (scanf_s("%d", &number) != 1)
    {
        printf("INPUT ERROR\n");
        return inputError;
    }
    if (number <= 0)
    {
        printf("INPUT ERROR\n");
        return inputError;
    }
    size_t result = solve((size_t)number);
    printf("Result: %zu\n", result);
    return 0;
}
