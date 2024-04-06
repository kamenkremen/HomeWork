#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Strings.h"
#include "ErrorCodes.h"

void deleteWords(char*** const words, const size_t size)
{
    if (words == NULL)
    {
        return;
    }
    for (size_t j = 0; j < size; ++j)
    {
        free((*words)[j]);
    }
    free(*words);
}

char* read(const char* const fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char* string = (char*)calloc(1, sizeof(char));
    size_t capacity = 1;
    size_t length = 0;
    if (string == NULL)
    {
        fclose(file);
        return NULL;
    }
    char symbol = getc(file);
    while (symbol != EOF)
    {
        if (length + 1 >= capacity)
        {
            capacity *= 2;
            char* buffer = realloc(string, capacity);
            if (buffer == NULL)
            {
                free(string);
                fclose(file);
                return NULL;
            }
            string = buffer;
        }
        string[length] = symbol;
        ++length;
        symbol = getc(file);
    }
    fclose(file);
    string[length] = '\0';
    return string;
}

char** getWords(const char* const string, size_t* const size, StringError* const errorCode)
{
    char** words = (char**)calloc(1, sizeof(char*));
    size_t currentWord = 0;
    size_t wordsCapacity = 1;
    size_t stringLength = strlen(string);
    size_t previousSpace = -1;
    char* word = NULL;
    for (size_t i = 0; i <= stringLength; ++i)
    {
        if (i == stringLength || string[i] == ' ')
        {
            if (i != stringLength && i != 0 && string[i - 1] == ' ')
            {
                previousSpace = i;
                continue;
            }
            if (currentWord >= wordsCapacity)
            {
                wordsCapacity *= 2;
                char** buffer = (char**)realloc(words, sizeof(char*) * wordsCapacity);
                if (buffer == NULL)
                {
                    deleteWords(&words, currentWord);
                    *errorCode = memoryError;
                    return NULL;
                }
                words = buffer;
                for (size_t j = currentWord; j < wordsCapacity; ++j)
                {
                    words[j] = NULL;
                }
            }
            word = (char*)calloc(i - previousSpace, sizeof(char));
            if (word == NULL)
            {
                deleteWords(&words, currentWord);
                *errorCode = memoryError;
                return NULL;
            }
            memcpy(word, string + previousSpace + 1, i - previousSpace - 1);
            words[currentWord] = word;
            ++currentWord;
            previousSpace = i;
        }
    }
    *size = currentWord;
    return words;
}
