#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define FIRST_SIZE 6
#define SECOND_SIZE 7

enum ReturnValues
{
    equal,
    first,
    second,
};

enum ErrorCodes
{
    ok,
    memoryError,
    nullPointerError,
};

int greater(const bool* const firstNumber, const bool* const secondNumber, const size_t firstSize, const size_t secondSize, int* const errorCode)
{
    if (firstNumber == NULL || secondNumber == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    size_t maxSize = (firstSize > secondSize ? firstSize : secondSize);
    bool* newFirstNumber = (bool*)calloc(maxSize, sizeof(bool));
    if (newFirstNumber == NULL)
    {
        *errorCode = memoryError;
        return memoryError;
    }
    bool* newSecondNumber = (bool*)calloc(maxSize, sizeof(bool));
    if (newSecondNumber == NULL)
    {
        *errorCode = memoryError;
        free(newFirstNumber);
        return memoryError;
    }
    for (size_t i = 0; i < firstSize; ++i)
    {
        newFirstNumber[maxSize - 1 - i] = firstNumber[firstSize - 1 - i];
    }
    for (size_t i = 0; i < secondSize; ++i)
    {
        newSecondNumber[maxSize - 1 - i] = secondNumber[secondSize - 1 - i];
    }
    for (size_t i = 0; i < maxSize; ++i)
    {
        if (newFirstNumber[i] && !newSecondNumber[i])
        {
            free(newFirstNumber);
            free(newSecondNumber);
            return first;
        }
        if (!newFirstNumber[i] && newSecondNumber[i])
        {
            free(newFirstNumber);
            free(newSecondNumber);
            return second;
        }
    }
    free(newFirstNumber);
    free(newSecondNumber);
    return equal;
}

int tests(void)
{
    bool firstNumber[3] = { true, true, true };
    bool secondNumber[4] = {false, true, true, true };
    int errorCode = ok;
    int result = greater(firstNumber, secondNumber, 3, 4, &errorCode);
    if (errorCode != ok || result != equal)
    {
        return 1;
    }
    firstNumber[0] = false;
    result = greater(firstNumber, secondNumber, 3, 4, &errorCode);
    if (errorCode != ok || result != second)
    {
        return 2;
    }
    firstNumber[0] = true;
    secondNumber[0] = true;
    result = greater(firstNumber, secondNumber, 3, 4, &errorCode);
    if (errorCode != ok || result != second)
    {
        return 3;
    }
    secondNumber[0] = false;
    secondNumber[1] = false;
    result = greater(firstNumber, secondNumber, 3, 4, &errorCode);
    if (errorCode != ok || result != first)
    {
        return 4;
    }
    return ok;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN TEST %d\n", errorCode);
        return errorCode;
    }
    const bool firstNumber[FIRST_SIZE] = { true, true, false, false, false, true };
    const bool secondNumber[SECOND_SIZE] = { true, true, false, true, true, true, true };
    errorCode = ok;
    int result = greater(firstNumber, secondNumber, FIRST_SIZE, SECOND_SIZE, &errorCode);
    if (result == first)
    {
        printf("First number is greater than second.\n");
    }
    else if (result == second)
    {
        printf("Second number is greater than first.\n");
    }
    else if (result == equal)
    {
        printf("First number is equal to the second number.\n");
    }
    return ok;
}
