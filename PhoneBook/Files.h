#pragma once

#include "PhoneBook.h"

// reads and parses phone book
bool readBook(char* numbers[MAX_SIZE], char* names[MAX_SIZE], size_t* const size, const char* const fileName);
//writes phone book to the file
bool writeBook(const char* const numbers[MAX_SIZE], const char* const names[MAX_SIZE], size_t* const size, const char* const fileName, size_t* const newRecordings);
