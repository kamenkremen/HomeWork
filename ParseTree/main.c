#include <stdio.h>
#include <stdlib.h>

#include "ParseTree.h"
#include "FileRead.h"
#include "Tests.h"
#include "ErrorCodes.h"

static int finish(ParseTree** const tree, const int errorCode)
{
    deleteParseTree(tree);
    return errorCode;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
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
        printf("TREE BUILDING ERROR\n");
        return finish(&tree, treeBuildingError);
    }
    printf("Expression in infix form:\n");
    printTree(tree);
    const int result = calculate(tree, &errorCode);
    if (errorCode != ok)
    {
        printf("ERROR IN CALCULATION\n");
        return finish(&tree, errorCode);
    }
    printf("Result of the expression: %d\n", result);
    return finish(&tree, ok);
}
