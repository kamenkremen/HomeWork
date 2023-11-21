#include <stdio.h>
#include <stdlib.h>

#include "SearchTree.h"
#include "Test.h"

bool* test()
{
    bool* failedCases[NUMBER_OF_TESTS] = { 0 };
    Tree* tree = createTree();
    if (delete(tree, 1234) != noSuchElement)
    {
        failedCases[0] = true;
    }
    if (tree == NULL)
    {
        failedCases[1] = true;
    }
    int errorCode = ok;
    if (contains(tree, 5, &errorCode) || errorCode != ok)
    {
        failedCases[2] = true;
    }
    if (add(tree, 5, "test") != ok)
    {
        failedCases[3] = true;
    }
    if (!contains(tree, 5, &errorCode) || errorCode != ok)
    {
        failedCases[4] = true;
    }
    if (get(tree, 5, &errorCode) != "test" || errorCode != ok)
    {
        failedCases[5] = true;
    }
    if (add(tree, 6, "test2") != ok)
    {
        failedCases[6] = true;
    }
    if (add(tree, 1, "test") != ok)
    {
        failedCases[7] = true;
    }
    if (get(tree, 1, &errorCode) != "test" || errorCode != ok)
    {
        failedCases[8] = true;
    }
    if (get(tree, 6, &errorCode) != "test2" || errorCode != ok)
    {
        failedCases[9] = true;
    }
    if (delete(tree, 6) != ok)
    {
        failedCases[10] = true;
    }
    if (contains(tree, 6, &errorCode) || errorCode != ok)
    {
        failedCases[11] = true;
    }
    if (delete(tree, 6) != noSuchElement)
    {
        failedCases[12] = true;
    }
    if (delete(tree, 7) != noSuchElement)
    {
        failedCases[13] = true;
    }
    deleteTree(&tree);
    return failedCases;
}
