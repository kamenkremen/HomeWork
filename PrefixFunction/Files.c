#include <stdlib.h>
#include <stdio.h>

#include "Files.h"

char* readFile(const char* const fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        fclose(file);
        return NULL;
    }
    size_t capacity = 1;
    size_t length = 0;
    char symbol = 0;
    while ((symbol = getc(file)) != EOF)
    {
        if (length >= capacity)
        {
            capacity *= 2;
            string = (char*)realloc(string, capacity);
            if (string == NULL)
            {
                fclose(file);
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
            fclose(file);
            return NULL;
        }
    }
    string[length] = '\0';
    fclose(file);
    return string;
}
