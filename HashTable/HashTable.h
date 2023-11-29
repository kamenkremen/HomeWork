#pragma once

#define HASH_SIZE 293

#include "List.h"

typedef struct Table Table;
void deleteTable(Table** const table);
void printTable(const Table* const table);
float averageListLength(const Table* const table, int* const errorCode);
size_t maxListLength(const Table* const table, int* const errorCode);
float loadFactor(const Table* const table, int* const errorCode);
int addToTable(Table* const table, const char* const word);
Table* createTable(void);
int addWordsToTable(Table* const table, const char* const string);
List* getList(const Table* const table, const size_t index);
