#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CommentsLexer.h"
#include "ErrorCodes.h"
#include "Files.h"

enum States
{
    notComment,
    afterSlash,
    comment,
    afterStar,
};

static bool relocate(char** const string, size_t* const capacity)
{
    *capacity *= 2;
    char* buffer = (char*)realloc(*string, *capacity);
    if (buffer == NULL)
    {
        free(*string);
        return true;
    }
    *string = buffer;
    return false;
}

char* getComments(const char* const string, const Table* const table)
{
    int state = notComment;
    size_t currentIndex = 0;
    size_t length = strlen(string);
    char* comments = (char*)calloc(1, sizeof(char));
    if (comments == NULL)
    {
        return NULL;
    }
    size_t capacity = 1;
    size_t size = 0;
    if (string == NULL)
    {
        return NULL;
    }
    for (size_t currentIndex = 0; currentIndex < length; ++currentIndex)
    {
        switch (state)
        {
        case comment:
            if (string[currentIndex] != '*')
            {
                if (size >= capacity)
                {
                    if (relocate(&comments, &capacity))
                    {
                        return NULL;
                    }
                }
                comments[size] = string[currentIndex];
                ++size;
            }
            state = table->table[state][string[currentIndex]];
            break;
        case afterStar:
            if (size + 1 >= capacity)
            {
                if (relocate(&comments, &capacity))
                {
                    return NULL;
                }
            }
            if (string[currentIndex] == '/')
            {
                comments[size] = '\n';
            }
            else
            {
                comments[size] = '*';
                ++size;
                comments[size] = string[currentIndex];
            }
            ++size;
        default:
            state = table->table[state][string[currentIndex]];
            break;
        }
    }
    comments[size - 1] = '\0';
    return comments;
}
