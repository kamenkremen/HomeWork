#pragma once

// reads string from file
char* readFile(const char* const fileName);
// returns parsed table for lexer
int** readTable(const char* const fileName, size_t* const lines);
