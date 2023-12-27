#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "Stack.h"
#include "ErrorCodes.h"

static int getPriority(const char operation)
{
    switch (operation)
    {
    case '*':
    case '/':
    case '%':
        return 3;
    case '+':
    case '-':
        return 2;
    case '=':
        return 1;
    default:
        return 0;
    }
}

static bool isOperation(const char c)
{
    return c == '+' || c == '-' || c == '/' || c == '*' || c == '=';
}

static bool isToken(const char c)
{
    return (bool)isdigit(c) || c == '(' || c == ')' || isOperation(c);
}

static int finish(Stack** const stack, char* const string, const char* const returnValue)
{
    if (stack != NULL)
    {
        freeStack(stack);
    }
    free(string);
    return returnValue;
}

static int write(char* const output, const char symbol, size_t* const current)
{
    output[*current] = symbol;
    output[++*current] = ' ';
    ++*current;
}

char* sortStation(const char* const string)
{
    Stack* stack = NULL;
    const size_t length = strlen(string);
    char* output = (char*)calloc(length + 1, sizeof(char));
    int errorCode = ok;
    size_t current = 0;
    if (output == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < length; ++i)
    {
        char symbol = string[i];
        if (!isToken(symbol))
        {
            if (symbol != ' ')
            {
                return finish(&stack, output, NULL);
            }
            continue;
        }
        if ((bool)isdigit(symbol))
        {
            write(output, symbol, &current);
            continue;
        }
        if (isOperation(symbol))
        {
            const currentPriority = getPriority(symbol);
            while (!isEmpty(stack) && isOperation(top(stack, &errorCode)) && getPriority(top(stack, &errorCode)) >= currentPriority)
            {
                write(output, top(stack, &errorCode), &current);
                pop(&stack);
            }
            if (push(&stack, symbol))
            {
                return finish(&stack, output, NULL);
            }
            continue;
        }
        if (symbol == '(')
        {
            if (push(&stack, symbol))
            {
                return finish(&stack, output, NULL);
            }
            continue;
        }
        if (symbol == ')')
        {
            while (!isEmpty(stack) && top(stack, &errorCode) != '(')
            {
                write(output, top(stack, &errorCode), &current);
                pop(&stack);
            }
            if (isEmpty(stack))
            {
                return finish(&stack, output, NULL);
            }
            pop(&stack);
            continue;
        }
    }
    while (!isEmpty(stack))
    {
        char symbol = top(stack, &errorCode);
        if (symbol == '(')
        {
            return finish(&stack, output, NULL);
        }
        write(output, top(stack, &errorCode), &current);
        pop(&stack);
    }
    freeStack(&stack);
    output[current - 1] = '\0';
    char* buffer = (char*)realloc(output, current);
    if (buffer == NULL)
    {
        return finish(NULL, output, NULL);
    }
    output = buffer;
    return output;
}
