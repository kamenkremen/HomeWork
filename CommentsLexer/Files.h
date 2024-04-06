#pragma once

// table with states
typedef struct Table {
    int** table;
    size_t lines;
    size_t columns;
} Table;
// reads string from file
char* readFile(const char* const fileName);
// returns parsed table for lexer
Table* readTable(const char* const fileName);
// free table
void freeTable(Table** const table);
