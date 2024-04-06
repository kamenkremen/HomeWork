#pragma once

#include "List.h"

typedef int TableError;

typedef struct Table Table;

void deleteTable(Table** const table);

void printTable(const Table* const table);

float averageListLength(const Table* const table, TableError* const errorCode);

size_t maxListLength(const Table* const table, TableError* const errorCode);

float loadFactor(const Table* const table, TableError* const errorCode);

TableError addToTable(Table* const table, const char* const word);

Table* createTable(const size_t hashSize);

size_t getBucketSize(const Table* const table, const size_t index);
