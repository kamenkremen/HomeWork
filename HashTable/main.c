#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#include "List.h"
#include "ErrorCodes.h"
#include "Strings.h"
//#include "Tests.h"

#define HASH_SIZE 293
#define MEMORY_ERROR_MESSAGE "MEMORY ERROR\n"

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    const char* const string = read("input.txt");
    if (string == NULL)
    {
        printf(MEMORY_ERROR_MESSAGE);
        return memoryError;
    }
    printf("%s\n", string);
    size_t size = 0;
    const char* const* const words = getWords(string, &size, &errorCode);
    free(string);
    if (errorCode != ok)
    {
        deleteWords(&words, size);
        printf(MEMORY_ERROR_MESSAGE);
        return memoryError;
    }
    Table* table = createTable(HASH_SIZE);
    if (table == NULL)
    {
        printf(MEMORY_ERROR_MESSAGE);
        deleteWords(&words, size);
        return memoryError;
    }
    for (size_t i = 0; i < size; ++i)
    {
        errorCode = addToTable(table, words[i]);
        if (errorCode != ok)
        {
            printf(MEMORY_ERROR_MESSAGE);
            deleteWords(&words, size);
            deleteTable(&table);
            return memoryError;
        }
    }
    printTable(table);
    printf("Average list length - %f\n", averageListLength(table, &errorCode));
    printf("Maximum list length - %zu\n", maxListLength(table, &errorCode));
    printf("Load factor - %f\n", loadFactor(table, &errorCode));
    deleteTable(&table);
    deleteWords(&words, size);
    return ok;
}
