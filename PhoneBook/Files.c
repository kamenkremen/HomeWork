#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "Files.h"

static char* readString(FILE* const file, const char end)
{
    if (file == NULL)
    {
        return NULL;
    }
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        return NULL;
    }
    size_t capacity = 1;
    size_t size = 0;
    char symbol = fgetc(file);
    for (; symbol != end && symbol != EOF; symbol = fgetc(file))
    {
        if (size + 1 >= capacity)
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
        string[size] = symbol;
        ++size;
    }
    string[size] = '\0';
    return string;
}

bool readBook(char* numbers[100], char* names[100], size_t* const size, const char* const fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return true;
    }
    *size = 0;
    while (true)
    {
        numbers[*size] = readString(file, ' ');
        if (strcmp(numbers[*size], "") == 0)
        {
            fclose(file);
            return false;
        }
        if (numbers[*size] == NULL)
        {
            for (size_t j = 0; j < *size; ++j)
            {
                free(names[j]);
                free(numbers[j]);
            }
            fclose(file);
            return true;
        }
        names[*size] = readString(file, '\n');
        if (names[*size] == NULL)
        {
            for (size_t j = 0; j < *size; ++j)
            {
                free(numbers[j]);
                free(names[j]);
            }
            free(numbers[*size]);
            fclose(file);
            return true;
        }
        ++(*size);
    }
    fclose(file);
    return false;
}

bool writeBook(const char* const numbers[100], const char* const names[100], size_t* const size, const char* const fileName, size_t* const newRecordings)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "a");
    if (file == NULL)
    {
        return true;
    }
    for (size_t i = *size; i < *size + *newRecordings; ++i)
    {
        if (fprintf(file, "%s %s\n", numbers[i], names[i]) < 0)
        {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    *size = *size + *newRecordings;
    *newRecordings = 0;
    return false;
}
