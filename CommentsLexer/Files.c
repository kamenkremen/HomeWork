#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Files.h"
#include "ErrorCodes.h"

#define CHAR_SIZE 256

static bool relocate(char** const string, size_t* const capacity)
{
    *capacity *= 2;
    char* buffer = (char*)realloc(*string, *capacity);
    if (buffer == NULL)
    {
        free(*string);
        return true;
    }
    *string = buffer;
    return false;
}

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
        if (length + 1>= capacity)
        {
            if (relocate(&string, &capacity))
            {
                fclose(file);
                return NULL;
            }
        }
        string[length] = symbol;
        ++length;
    }
    fclose(file);
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

static Table* createTable(const size_t lines, const size_t columns)
{
    Table* table = (Table*)calloc(1, sizeof(Table));
    if (table == NULL)
    {
        return NULL;
    }
    table->lines = lines;
    table->columns = columns;
    table->table = (int**)calloc(lines, sizeof(int*));
    if (table->table == NULL)
    {
        free(table);
        return NULL;
    }
    for (size_t i = 0; i < lines; ++i)
    {
        table->table[i] = (int*)calloc(columns, sizeof(int));
        if (table->table[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(table->table[j]);
                free(table->table);
                free(table);
                return NULL;
            }
        }
    }
    return table;
}

static int finish(Table** const table, FILE** const file, char** const header)
{
    freeTable(table);
    fclose(*file);
    free(*header);
    return NULL;
}

Table* readTable(const char* const fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    size_t lines = 0;
    fscanf_s(file, "%zu", &lines);
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
    Table* table = createTable(lines, CHAR_SIZE);
    if (table == NULL)
    {
        fclose(file);
        return NULL;
    }
    for (size_t i = 0; i < lines; ++i)
    {
        char symbol = getc(file);
        if (symbol == EOF)
        {
            return finish(&table, &file, &header);
        }
        int defaultState = symbol - '0';
        for (size_t j = 0; j < table->columns; ++j)
        {
            table->table[i][j] = defaultState;
        }
        for (size_t j = 0; j < columns; ++j)
        {
            symbol = getc(file);
            if (symbol == EOF)
            {
                return finish(&table, &file, &header);
            }
            table->table[i][header[j]] = symbol - '0';
        }
        symbol = getc(file);
        if (symbol == EOF && i != lines - 1)
        {
            return finish(&table, &file, &header);
        }

    }
    fclose(file);
    free(header);
    return table;
}

void freeTable(Table** const table)
{
    for (size_t i = 0; i < (*table)->lines; ++i)
    {
        free(((*table)->table)[i]);
    }
    free(*table);
}
