#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            const char* const buffer = (char*)realloc(string, capacity);
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
        const char* const buffer = (char*)realloc(string, capacity);
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


char* stringCopy(const char* const string)
{
    char* newString = (char*)calloc(strlen(string) + 1, sizeof(char));
    if (newString == NULL)
    {
        return NULL;
    }
    strcpy_s(newString, strlen(string) + 1, string);
    return newString;
}
