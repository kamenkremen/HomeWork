#include <stdio.h>
#include <stdlib.h>

#include "ParseTree.h"
#include "FileRead.h"
#include "Tests.h"
#include "ErrorCodes.h"

char* TEST_ERROCODES[3] =
{
    "",
    "FILE READING TEST",
    "PARSE TREE TEST",
};

int finish(ParseTree** const tree, const int errorCode)
{
    deleteParseTree(tree);
    return errorCode;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN %s, CASE %d\n", TEST_ERROCODES[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    char* string = read("input.txt");
    if (string == NULL)
    {
        printf("FILE ERROR\n");
        return fileError;
    }
    ParseTree* tree = build(string);
    if (tree == NULL)
    {
        printf("MEMORY ERROR\n");
        return finish(&tree, errorCode);
    }
    printf("Expression in infix form:\n");
    printTree(tree);
    int result = calculate(tree, &errorCode);
    if (errorCode != ok)
    {
        printf("NULL POINTER ERROR\n");
        return finish(&tree, errorCode);
    }
    printf("%d", result);
    return finish(&tree, ok);
}