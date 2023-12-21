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

static void deleteMatrix(int*** const matrix, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(*matrix[i]);
    }
    free(*matrix);
}

int** readTable(const char* const fileName, size_t* const lines)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    fscanf_s(file, "%zu", lines);
    size_t columns = 0;
    fscanf_s(file, "%zu", &columns);
    getc(file);
    char* header = (char*)calloc(columns, sizeof(char));
    if (header == NULL)
    {
        fclose(file);
        return NULL;
    }
    size_t capacity = 1;
    size_t headerSize = 0;
    char symbol = 0;
    for (size_t i = 0; i < columns; ++i)
    {
        symbol = getc(file);
        header[i] = symbol;
    }
    getc(file);
    int** table = (int**)calloc(*lines, sizeof(int*));
    for (size_t i = 0; i < *lines; ++i)
    {
        table[i] = (int*)calloc(256, sizeof(int));
        if (table[i] == NULL)
        {
            deleteMatrix(&table, i);
            free(header);
            fclose(file);
            return NULL;
        }
        int defaultState = getc(file) - '0';
        for (size_t j = 0; j < 256; ++j)
        {
            table[i][j] = defaultState;
        }
        for (size_t j = 0; j < columns; ++j)
        {
            table[i][header[j]] = getc(file) - '0';
        }
        getc(file);
    }
    fclose(file);
    free(header);
    return table;
}
