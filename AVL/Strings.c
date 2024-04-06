#include <stdio.h>
#include <stdlib.h>

#include "Strings.h"
#include "ErrorCodes.h"

char* readLine(int* const errorCode)
{
    char symbol = 0;
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        return memoryError;
    }
    size_t capacity = 1;
    size_t length = 0;
    while ((symbol = getchar()) != '\n')
    {
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
