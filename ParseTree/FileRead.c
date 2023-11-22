#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "FileRead.h"

char* read(const char* const fileName)
{
    FILE* file = fopen(fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char* string = (char*)calloc(1, sizeof(char));
    size_t capacity = 1;
    size_t length = 0;
    if (string == NULL)
    {
        fclose(file);
        return NULL;
    }
    char symbol = getc(file);
    while (symbol != "\n" && symbol != EOF)
    {
        if (length >= capacity)
        {
            capacity *= 2;
            string = realloc(string, capacity);
            if (string == NULL)
            {
                fclose(file);
                return NULL;
            }
        }
        string[length] = symbol;
        ++length;
        symbol = getc(file);
    }
    fclose(file);
    if (length >= capacity)
    {
        ++capacity;
        string = realloc(&string, capacity);
        if (string == NULL)
        {
            return NULL;
        }
    }
    string[length] = '\0';
    return string;
}