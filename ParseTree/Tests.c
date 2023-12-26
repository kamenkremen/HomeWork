#include <stdlib.h>
#include <stdio.h>

#include "FileRead.h"
#include "ParseTree.h"
#include "Tests.h"
#include "ErrorCodes.h"


static int testFileReading(void)
{
    char* test1 = read("test.txt");
    if (test1 = NULL || strcmp(test1, "(* (+ 1 1) 2)") != 0)
    {
        return 1;
    }
    char* test2 = read("test2.txt");
    if (test2 == NULL || strcmp(test2, "(- (+ (/ (* 3 2) 2) 8) 1234)") != 0)
    {
        return 2;
    }
    char* test3 = read("test3.txt");
    if (test3 == NULL || strcmp(test3, "") != 0)
    {
        return 3;
    }
    char* test4 = read("test4.txt");
    if (test4 == NULL || strcmp(test4, "(* (1 + 1) 2)") != 0)
    {
        return 4;
    }
    return ok;
}

static int testParseTree(void)
{
    ParseTree* tree1 = build(read("test.txt"));
    if (tree1 == NULL)
    {
        return 1;
    }
    int errorCode = ok;
    if (calculate(tree1, &errorCode) != 4 || errorCode != ok)
    {
        deleteParseTree(&tree1);
        return 2;
    }
    deleteParseTree(&tree1);
    ParseTree* tree2 = build(read("test2.txt"));
    if (tree2 == NULL)
    {
        return 3;
    }
    if (calculate(tree2, &errorCode) != -1223 || errorCode != ok)
    {
        deleteParseTree(&tree2);
        return 4;
    }
    deleteParseTree(&tree2);
    ParseTree* tree3 = build(read("test4.txt"));
    if (tree3 != NULL)
    {
        deleteParseTree(tree3);
        return 5;
    }
    return ok;
}


bool tests(void)
{
    int errorCode = testFileReading();
    bool isError = false;
    if (errorCode != ok)
    {
        isError = true;
        printf("ERROR IN FILE READING TESTS, CASE %d\n", errorCode);
    }
    errorCode = testParseTree();
    if (errorCode != ok)
    {
        isError = true;
        printf("ERROR IN PARSE TREE TESTS, CASE %d\n", errorCode);
    }
    return isError;
}
