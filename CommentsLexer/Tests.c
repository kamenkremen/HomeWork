#include <stdlib.h>
#include <string.h>

#include "CommentsLexer.h"
#include "Files.h"
#include "ErrorCodes.h"

static int finish(char* comments, const int returnValue, int** const table, const size_t lines)
{
    for (size_t i = 0; i < lines; ++i)
    {
        free(table[i]);
    }
    free(table);
    free(comments);
    return returnValue;
}

static int commentsLexerTest(void)
{
    size_t lines = 0;
    const int* const* const table = readTable("table.txt", &lines);
    int errorCode = ok;
    char* comments = getComments("test/*test*/", table, &errorCode);
    if (comments == NULL || strcmp(comments, "test") != 0 || errorCode != ok)
    {
        return finish(comments, 1, table, lines);
    }
    free(comments);
    comments = getComments("test", table);
    if (comments == NULL || strcmp(comments, "") != 0)
    {
        return finish(comments, 2, table, lines);
    }
    comments = getComments("\nnot a comment/*comment*/\n/ * comment(i lied) * /\n/*another* / comment*/", table);
    if (comments == NULL || strcmp(comments, "comment\nanother* / comment") != 0)
    {
        return finish(comments, 3, table, lines);
    }
    return finish(comments, ok, table, lines);
}

int tests(void)
{
    const int result = commentsLexerTest();
    if (result != ok)
    {
        printf("ERROR IN COMMENTS LEXER TEST, CASE %d\n", result);
    }
    return result;
}
