#pragma once

typedef int StringError;

char* read(const char* const fileName);

char** getWords(const char* const string, size_t* const size, StringError* const errorCode);

void deleteWords(char*** const words, const size_t size);
