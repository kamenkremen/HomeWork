#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HashTable.h"
#include "List.h"
#include "ErrorCodes.h"

struct Table
{
    size_t size;
    List** hashes;
};

static int hash(const char* const string, const size_t size)
{
    // разве если вынести взятие по модулю из этой функции, то не будет очень быстро происходить переполнение?
    int result = 0;
    for (size_t i = 0; i < strlen(string); ++i)
    {
        result = (result * 257 + string[i]) % size;
    }
    return result;
}

Table* createTable(const size_t hashSize)
{
    Table* newTable = (Table*)calloc(1, sizeof(Table));
    if (newTable == NULL)
    {
        return newTable;
    }
    newTable->size = hashSize;
    newTable->hashes = (List**)calloc(hashSize, sizeof(List*));
    if (newTable->hashes == NULL)
    {
        free(newTable);
        return NULL;
    }
    return newTable;
}

TableError addToTable(Table* const table, const char* const value)
{
    if (table == NULL)
    {
        return nullPointerError;
    }
    const int hashWord = hash(value, table->size);

    if (table->hashes[hashWord] == NULL)
    {
        table->hashes[hashWord] = createList();
        if (table->hashes[hashWord] == NULL)
        {
            return memoryError;
        }
    }
    const char* const valueCopy = (char*)calloc(strlen(value), sizeof(char));
    if (valueCopy == NULL)
    {
        return memoryError;
    }
    strcpy_s(valueCopy, strlen(value) + 1, value);
    return addWord(table->hashes[hashWord], valueCopy);
}

float loadFactor(const Table* const table, TableError* const errorCode)
{
    if (table == NULL)
    {
        *errorCode = nullPointerError;
        return 0;
    }
    size_t amount = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] != NULL)
        {
            ++amount;
        }
    }
    return (float)amount / (float)table->size;
}

size_t maxListLength(const Table* const table, TableError* const errorCode)
{
    if (table == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    size_t maxLength = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }
        size_t size = getSize(table->hashes[i]);
        maxLength = size > maxLength ? size : maxLength;
    }
    return maxLength;
}

float averageListLength(const Table* const table, TableError* const errorCode)
{
    if (table == NULL)
    {
        *errorCode = nullPointerError;
        return 0;
    }
    size_t amountOfLists = 0;
    size_t amountOfNodes = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] != NULL)
        {
            ++amountOfLists;
            amountOfNodes += getSize(table->hashes[i]);
        }
    }
    if (amountOfLists == 0)
    {
        return 0;
    }
    return (float)amountOfNodes / amountOfLists;
}

void printTable(const Table* const table)
{
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] != NULL)
        {
            printList(table->hashes[i]);
        }
    }
}

void deleteTable(Table** const table)
{
    for (size_t i = 0; i < (*table)->size; ++i)
    {
        if ((*table)->hashes[i] != NULL)
        {
            deleteList(&((*table)->hashes[i]));
        }
    }
    free((*table)->hashes);
    free(*table);
}

size_t getBucketSize(const Table* const table, const size_t index)
{
    if (table == NULL || index >= table->size)
    {
        return 0;
    }
    return getSize(table->hashes[index]);
}