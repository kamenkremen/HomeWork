#include <stdlib.h>
#include <stdio.h>

#include "Tests.h"
#include "ErrorCodes.h"
#include "AVL.h"

static int finish(Tree** const tree, const int returnValue)
{
    deleteTree(tree);
    return returnValue;
}

static int testAVL(void)
{
    Tree* tree = createTree();
    if (tree == NULL)
    {
        return finish(&tree, 1);
    }
    int errorCode = insert(tree, "test0", "test1");
    if (errorCode != ok)
    {
        return finish(&tree, 2);
    }
    if (strcmp(getValue(tree, "test1"), "test0") != 0)
    {
        return finish(&tree, 3);
    }
    errorCode = insert(tree, "test1", "test1");
    if (errorCode != ok)
    {
        return finish(&tree, 4);
    }
    if (strcmp(getValue(tree, "test1"), "test1") != 0)
    {
        return finish(&tree, 5);
    }
    errorCode = insert(tree, "test3", "test3");
    if (errorCode != ok)
    {
        return finish(&tree, 6);
    }
    if (strcmp(getValue(tree, "test3"), "test3") != 0)
    {
        return finish(&tree, 7);
    }
    errorCode = insert(tree, "test2", "test2");
    if (errorCode != ok)
    {
        return finish(&tree, 8);
    }
    if (strcmp(getValue(tree, "test2"), "test2") != 0)
    {
        return finish(&tree, 9);
    }
    if (deleteElement(tree, "test2"))
    {
        return finish(&tree, 10);
    }
    if (isContains(tree, "test2"))
    {
        return finish(&tree, 11);
    }
    if (deleteElement(tree, "test3"))
    {
        return finish(&tree, 12);
    }
    if (isContains(tree, "test3"))
    {
        return finish(&tree, 13);
    }
    if (deleteElement(tree, "test1"))
    {
        return finish(&tree, 14);
    }
    if (isContains(tree, "test1"))
    {
        return finish(&tree, 15);
    }
    return finish(&tree, ok);
}

int tests(void)
{
    const int errorCode = testAVL();
    if (errorCode != ok)
    {
        printf("ERROR IN AVL TESTS, CASE %d\n", errorCode);
    }
    return errorCode;
}
