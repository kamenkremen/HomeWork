#include <stdlib.h>
#include <string.h>

#include "CommentsLexer.h"
#include "Files.h"
#include "ErrorCodes.h"

static int finish(char* comments, const int returnValue, Table** const table, const size_t lines)
{
    freeTable(table);
    free(comments);
    return returnValue;
}

static int commentsLexerTest(void)
{
    const Table* const table = readTable("table.txt");
    if (table == NULL)
    {
        return 1;
    }
    size_t lines = table->lines;
    int errorCode = ok;
    char* comments = getComments("test/*test*/", table, &errorCode);
    if (comments == NULL || strcmp(comments, "test") != 0 || errorCode != ok)
    {
        return finish(comments, 1, &table, lines);
    }
    free(comments);
    comments = getComments("test", table);
    if (comments == NULL || strcmp(comments, "") != 0)
    {
        return finish(comments, 2, &table, lines);
    }
    comments = getComments("\nnot a comment/*comment*/\n/ * comment(i lied) * /\n/*another* / comment*/", table);
    if (comments == NULL || strcmp(comments, "comment\nanother* / comment") != 0)
    {
        return finish(comments, 3, &table, lines);
    }
    return finish(comments, ok, &table, lines);
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
