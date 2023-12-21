#include <stdlib.h>
#include <stdio.h>

#include "Files.h"
#include "CommentsLexer.h"
#include "ErrorCodes.h"
#include "Tests.h"

#define FAILED_TEST 1;

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return FAILED_TEST;
    }
    size_t lines = 0;
    const int* const * const table = readTable("table.txt", &lines);
    const char* const string = readFile("file.txt");
    const char* const comments = getComments(string, table, &errorCode);
    free(string);
    for (size_t i = 0; i < lines; ++i)
    {
        free(table[i]);
    }
    free(table);
    if (errorCode != ok)
    {
        printf("MEMORY ERROR\n");
        free(comments);
        return errorCode;
    }
    printf("Comments:\n%s\n", comments);
    free(comments);
    return ok;
}
