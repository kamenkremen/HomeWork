#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CommentsLexer.h"
#include "ErrorCodes.h"

enum States
{
    notComment,
    afterSlash,
    comment,
    afterStar,
};

char* getComments(const char* const string, const int* const* const table)
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
                    capacity *= 2;
                    char* buffer = (char*)realloc(comments, capacity);
                    if (buffer == NULL)
                    {
                        free(comments);
                        return;
                    }
                    comments = buffer;
                }
                comments[size] = string[currentIndex];
                ++size;
            }
            state = table[state][string[currentIndex]];
            break;
        case afterStar:
            if (size + 1 >= capacity)
            {
                capacity *= 2;
                char* buffer = (char*)realloc(comments, capacity);
                if (buffer == NULL)
                {
                    free(comments);
                    return;
                }
                comments = buffer;
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
            state = table[state][string[currentIndex]];
            break;
        }
    }
    comments[size - 1] = '\0';
    return comments;
}
