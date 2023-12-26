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
    for (;symbol != '\n' && symbol != EOF; symbol = getc(file))
    {
        if (length + 1 >= capacity)
        {
            capacity *= 2;
            char* buffer = (char*)realloc(string, capacity);
            if (buffer == NULL)
            {
                free(string);
                fclose(file);
                return NULL;
            }
            string = buffer;
        }
        string[length] = symbol;
        ++length;
    }
    fclose(file);
    string[length] = '\0';
    return string;
}
