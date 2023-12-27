#pragma once

// reads and parses phone book
bool readBook(char* numbers[100], char* names[100], size_t* const size, const char* const fileName);
//writes phone book to the file
bool writeBook(const char* const numbers[100], const char* const names[100], size_t* const size, const char* const fileName, size_t* const newRecordings);
