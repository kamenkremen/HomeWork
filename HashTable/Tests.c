#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Tests.h"
#include "HashTable.h"
#include "List.h"
#include "ErrorCodes.h"
#include "Strings.h"

#define MAX_STRING_LENGTH 10
#define MIN_STRING_LENGTH 2
#define MAX_CHAR_SIZE 256
#define AMOUNT_OF_WORDS 1000000
#define MAX_DURATION 10

static int finish(Table** const table, const int errorCode)
{
    deleteTable(table);
    return errorCode;
}

static char* generateWord(void)
{
    size_t size = MIN_STRING_LENGTH + rand() % MAX_STRING_LENGTH;
    char* word = (char*)calloc(size, sizeof(char));
    if (word == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < size - 1; ++i)
    {
        word[i] = rand() % MAX_CHAR_SIZE;
    }
    word[size - 1] = '/0';
    return word;
}

static int hashTableLoadTest(void)
{
    Table* table = createTable(100000);
    clock_t before = clock();
    for (size_t i = 0; i < AMOUNT_OF_WORDS; ++i)
    {
        char* word = generateWord();
        if (word == NULL)
        {
            return finish(&table, 1);
        }
        int errorCode = addToTable(table, word);
        if (errorCode != ok)
        {
            return finish(&table, 1);
        }
    }
    clock_t after = clock();
    double duration = (double)(after - before) / CLOCKS_PER_SEC;
    if (duration > MAX_DURATION)
    {
        return finish(&table, 2);
    }
    return ok;
}

static int testHashTable(void)
{
    const char* const string = read("test1.txt");
    if (string == NULL)
    {
        return 1;
    }
    int errorCode = ok;
    size_t size = 0;
    const char* const* const words = getWords(string, &size, &errorCode);
    free(string);
    if (errorCode != ok)
    {
        deleteWords(&words, size);
        return 2;
    }
    Table* table = createTable(3);
    if (table == NULL)
    {
        deleteWords(&words, size);
        return 3;
    }
    for (size_t i = 0; i < size; ++i)
    {
        char* wordCopy = (char*)calloc(strlen(words[i]) + 1, sizeof(char));
        if (wordCopy == NULL)
        {
            deleteWords(&words, size);
            deleteTable(&table);
            return 4;
        }
        strcpy_s(wordCopy, strlen(words[i]) + 1, words[i]);
        if (wordCopy == NULL)
        {
            deleteWords(&words, size);
            deleteTable(&table);
            return 4;
        }
        errorCode = addToTable(table, wordCopy);
        if (errorCode != ok)
        {
            deleteWords(&words, size);
            deleteTable(&table);
            return 4;
        }
    }
    deleteWords(&words, size);
    if (getBucketSize(table, 0) != 2 || getBucketSize(table, 1) != 1 || getBucketSize(table, 2) != 1)
    {
        return finish(&table, 5);
    }
    return finish(&table, ok);
}

int tests(void)
{
    srand(time(NULL));
    int errorCode = testHashTable();
    if (errorCode != ok)
    {
        printf("ERROR IN HASH TABLE TEST, CASE %d\n", errorCode);
    }
    if (hashTableLoadTest() != ok)
    {
        printf("HASH TABLE IS TOO SLOW\n");
        errorCode = 2;
    }
    return errorCode;
}
