#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "HashTable.h"
#include "List.h"
#include "ErrorCodes.h"

struct Table
{
    size_t amount;
    size_t size;
    List* hashes[HASH_SIZE];
};

static int hash(const char* const string)
{
    int result = 0;
    for (size_t i = 0; i < strlen(string); ++i)
    {
        result = (result * 257 + string[i]) % HASH_SIZE;
    }
    return result;
}

Table* createTable(void)
{
    Table* newTable = (Table*)calloc(1, sizeof(Table));
    if (newTable == NULL)
    {
        return newTable;
    }
    newTable->size = HASH_SIZE;
    newTable->amount = 0;
    return newTable;
}

int addToTable(Table* const table, const char* const value)
{

    if (table == NULL)
    {
        return nullPointerError;
    }
    const int hashWord = hash(value);

    if (table->hashes[hashWord] == NULL)
    {
        table->hashes[hashWord] = createList();
        if (table->hashes[hashWord] == NULL)
        {
            return memoryError;
        }
    }
    if (!isContains(table->hashes[hashWord], value))
    {
        ++table->amount;
    }
    return addWord(table->hashes[hashWord], value);
}

float loadFactor(const Table* const table, int* const errorCode)
{
    if (table == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    return (float)table->amount / (float)table->size;
}

size_t maxListLength(const Table* const table, int* const errorCode)
{
    if (table == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    int maxLength = 0;
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

float averageListLength(const Table* const table, int* const errorCode)
{
    if (table == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
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
        ++amountOfLists;
    }
    return (float)amountOfNodes / (float)amountOfLists;
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

List* getList(const Table* const table, const size_t index)
{
    if (table == NULL || index >= table->size)
    {
        return NULL;
    }
    return table->hashes[index];
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
    free(*table);
}

int addWordsToTable(Table* const table, const char* const string)
{
    char* word = (char*)calloc(1, sizeof(char));
    size_t capacity = 1;
    size_t wordLength = 0;
    if (word == NULL)
    {
        return memoryError;
    }
    size_t length = strlen(string);
    for (size_t i = 0; i < length; ++i)
    {
        if (string[i] == ' ' || string[i] == '\n')
        {
            if (wordLength == 0)
            {
                continue;
            }
            word[wordLength] = '\0';
            int errorCode = addToTable(table, word);
            if (errorCode != ok)
            {
                free(word);
                return errorCode;
            }
            word = (char*)calloc(1, sizeof(char));
            wordLength = 0;
            capacity = 1;
            if (word == NULL)
            {
                return memoryError;
            }
        }
        else
        {
            word[wordLength] = string[i];
            ++wordLength;
            if (wordLength >= capacity)
            {
                capacity *= 2;
                word = (char*)realloc(word, capacity);
                if (word == NULL)
                {
                    return memoryError;
                }
            }
        }
    }
    word[wordLength] = '\0';
    int errorCode = addToTable(table, word);
    return errorCode;
}
