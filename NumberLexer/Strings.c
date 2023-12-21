#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Strings.h"

char* readLine(void)
{
    char symbol = 0;
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }
    size_t capacity = 1;
    size_t length = 0;
    while ((symbol = getchar()) != '\n')
    {
        if (length >= capacity)
        {
            capacity *= 2;
            char* buffer = (char*)realloc(string, capacity);
            if (buffer == NULL)
            {
                free(string);
                return NULL;
            }
            string = buffer;
        }
        string[length] = symbol;
        ++length;
    }
    if (length >= capacity)
    {
        ++capacity;
        char* buffer = (char*)realloc(string, capacity);
        if (buffer == NULL)
        {
            free(string);
            return NULL;
        }
        string = buffer;
    }
    string[length] = '\0';
    return string;
}
