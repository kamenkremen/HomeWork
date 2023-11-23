#include <stdio.h>
#include <stdlib.h>

#include "ReadFile.h"
#include "ErrorCodes.h"

char* read(int* const errorCode)
{
    char symbol = 0;
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        return memoryError;
    }
    size_t capacity = 1;
    size_t length = 0;
    size_t amountOfNumbers = 0;
    while ((symbol = getchar()) != '\n')
    {
        if (symbol == ' ')
        {
            continue;
        }
        if ((int)(symbol - '0') < 0 || (int)(symbol - '0') > 9)
        {
            if (symbol != '/' && symbol != '*' && symbol != '+' && symbol != '-' || amountOfNumbers < 2)
            {
                free(string);
                *errorCode = inputError;
                return NULL;
            }
            --amountOfNumbers;
        }
        else
        {
            ++amountOfNumbers;
        }
        if (length >= capacity)
        {
            capacity *= 2;
            string = (char*)realloc(string, capacity);
            if (string == NULL)
            {
                *errorCode = memoryError;
                return NULL;
            }
        }
        string[length] = symbol;
        ++length;
    }
    if (length >= capacity)
    {
        ++capacity;
        string = (char*)realloc(string, capacity);
        if (string == NULL)
        {
            *errorCode = memoryError;
            return NULL;
        }
    }
    string[length] = '\0';

    return string;
}