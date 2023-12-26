#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SearchTree.h"
#include "Test.h"

static int finish(Tree* const tree, const int returnValue)
{
    deleteTree(&tree);
    return returnValue;
}

static int treeTest(void)
{
    Tree* tree = createTree();
    if (delete(tree, 1234))
    {
        return finish(tree, 1);
    }
    if (tree == NULL)
    {
        return finish(tree, 2);
    }
    int errorCode = ok;
    if (contains(tree, 5, &errorCode) || errorCode != ok)
    {
        return finish(tree, 3);
    }
    if (add(tree, 5, "test") != ok)
    {
        return finish(tree, 4);
    }
    if (!contains(tree, 5, &errorCode) || errorCode != ok)
    {
        return finish(tree, 5);
    }
    if (strcmp(get(tree, 5, &errorCode), "test") != 0 || errorCode != ok)
    {
        return finish(tree, 6);
    }
    if (add(tree, 6, "test2") != ok)
    {
        return finish(tree, 7);
    }
    if (add(tree, 1, "test") != ok)
    {
        return finish(tree, 8);
    }
    if (strcmp(get(tree, 1, &errorCode), "test") != 0 || errorCode != ok)
    {
        return finish(tree, 9);
    }
    if (strcmp(get(tree, 6, &errorCode), "test2") != 0 || errorCode != ok)
    {
        return finish(tree, 10);
    }
    if (delete(tree, 6))
    {
        return finish(tree, 11);
    }
    if (contains(tree, 6, &errorCode) || errorCode != ok)
    {
        return finish(tree, 12);
    }
    if (delete(tree, 6))
    {
        return finish(tree, 13);
    }
    if (delete(tree, 7))
    {
        return finish(tree, 14);
    }
    return finish(tree, 0);
}

int tests(void)
{
    const int errorCode = treeTest();
    if (errorCode != ok)
    {
        printf("ERROR IN TESTS, CASE %d\n", errorCode);
    }
    return errorCode;
}
