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
    const Table* const table = readTable("table.txt", &lines);
    if (table == NULL)
    {
        printf("MEMORY ERROR\n");
        return memoryError;
    }
    const char* const string = readFile("file.txt");
    if (string == NULL)
    {
        freeTable(&table);
        printf("MEMORY ERROR\n");
        return memoryError;
    }
    const char* const comments = getComments(string, table, &errorCode);
    free(string);
    freeTable(&table);
    if (errorCode != ok || comments == NULL)
    {
        printf("MEMORY ERROR\n");
        free(comments);
        return errorCode;
    }
    printf("Comments:\n%s\n", comments);
    free(comments);
    return ok;
}
