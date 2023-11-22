#include <stdlib.h>
#include <stdio.h>

#include "FileRead.h"
#include "ParseTree.h"
#include "Tests.h"
#include "ErrorCodes.h"


static int testFileReading(void)
{
    char* test1 = read("test.txt");
    if (strcmp(test1, "(* (+ 1 1) 2)") != 0)
    {
        return 1;
    }
    char* test2 = read("test2.txt");
    if (strcmp(test2, "(- (+ (/ (* 3 2) 2) 8) 1234)") != 0)
    {
        return 2;
    }
    char* test3 = read("test3.txt");
    if (strcmp(test3, "") != 0)
    {
        return 3;
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
    return ok;
}


int tests(void)
{
    int errorCode = testFileReading();
    if (errorCode != ok)
    {
        return 10 + errorCode;
    }
    errorCode = testParseTree();
    if (errorCode != ok)
    {
        return 20 + errorCode;
    }
    return ok;
}