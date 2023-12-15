#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ErrorCodes.h"
#include "Strings.h"

static int* prefixFunction(const char* const string, const char* const subString)
{
    if (string == NULL || subString == NULL)
    {
        return NULL;
    }
    size_t length = strlen(string);
    size_t* pi = (size_t*)calloc(strlen(string), sizeof(size_t));
    if (pi == NULL)
    {
        return NULL;
    }
    for (size_t i = 1; i < length; ++i)
    {
        size_t current = pi[i - 1];
        while (string[i] != subString[current] && current >= 1)
        {
            current = pi[current - 1];
        }
        if (string[i] == subString[current])
        {
            pi[i] = current + 1;
        }
    }
    return pi;
}

int findSubString(const char* const string, const char* const subString, int* const errorCode)
{
    if (string == NULL || subString == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    size_t* pi = prefixFunction(string, subString);
    if (pi == NULL)
    {
        *errorCode = memoryError;
        return memoryError;
    }
    size_t size = strlen(string);
    size_t subStringSize = strlen(subString);
    for (size_t i = 0; i < size; ++i)
    {
        if (pi[i] == subStringSize)
        {
            return i - subStringSize;
        }
    }
    return -1;
}


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
            string = (char*)realloc(string, capacity);
            if (string == NULL)
            {
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
            return NULL;
        }
    }
    string[length] = '\0';
    return string;
}