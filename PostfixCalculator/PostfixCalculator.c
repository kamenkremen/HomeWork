#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "PostfixCalculator.h"
#include "ErrorCodes.h"

static int processTheOperation(const char operation, const int firstNumber, const int secondNumber, int* const errorCode)
{
    switch (operation)
    {
    case  '-':
        return firstNumber - secondNumber;
    case '+':
        return firstNumber + secondNumber;
    case '*':
        return firstNumber * secondNumber;
    case '/':
        if (secondNumber == 0)
        {
            *errorCode = division0Error;
            return 0;
        }
        return firstNumber / secondNumber;
    default:
        return 0;
    }
}

static int finish(Stack** const stack, int* const mainErrorCode, const int errorCode)
{

    if (*stack != NULL)
    {
        freeStack(stack);
    }
    *mainErrorCode = errorCode;
    return errorCode;
}

static bool isCorrect(const char* const string)
{
    int amountOfNumbers = 0;
    for (size_t i = 0; i < strlen(string); ++i)
    {
        char symbol = string[i];
        if (symbol == ' ')
        {
            continue;
        }
        if ((int)(symbol - '0') < 0 || (int)(symbol - '0') > 9)
        {
            if (symbol != '/' && symbol != '*' && symbol != '+' && symbol != '-' || amountOfNumbers < 2)
            {
                return false;
            }
            --amountOfNumbers;
        }
        else
        {
            ++amountOfNumbers;
        }
    }
    return true;
}

int postfixCalculator(const char* const string, int* const mainErrorCode)
{
    if (!isCorrect(string))
    {
        *mainErrorCode = inputError;
        return inputError;
    }
    Stack* stack = NULL;
    for (size_t i = 0; i < strlen(string); ++i)
    {
        if (string[i] == ' ')
        {
            continue;
        }
        if (string[i] == '-' || string[i] == '/' || string[i] == '*' || string[i] == '+')
        {
            int errorCode = ok;
            const int secondNumber = top(stack, &errorCode);
            if (errorCode != ok)
            {
                return finish(&stack, mainErrorCode, errorCode);
            }
            pop(&stack);
            const int firstNumber = top(stack, &errorCode);
            if (errorCode != ok)
            {
                return finish(&stack, mainErrorCode, errorCode);
            }
            pop(&stack);
            const int thirdNumber = processTheOperation(string[i], firstNumber, secondNumber, &errorCode);
            if (errorCode != ok)
            {
                return finish(&stack, mainErrorCode, errorCode);
            }
            if (push(&stack, thirdNumber) != ok)
            {
                return finish(&stack, mainErrorCode, memoryError);
            }
        }
        else
        {
            if (string[i] - '0' < 0 || string[i] - '0' > 9)
            {
                return finish(&stack, mainErrorCode, inputError);
            }
            if (push(&stack, (int)string[i] - '0') != ok)
            {
                return finish(&stack, mainErrorCode, memoryError);
            }
        }
    }
    int errorCode = ok;
    const int result = top(stack, &errorCode);
    if (errorCode != ok)
    {
        return finish(&stack, mainErrorCode, errorCode);
    }
    pop(&stack);
    if (!isEmpty(stack))
    {
        return finish(&stack, mainErrorCode, stackError);
    }
    freeStack(&stack);
    return result;
}
