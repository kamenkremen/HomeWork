#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "ErrorCodes.h"
#include "AVL.h"
#include "Strings.h"

enum Operations
{
    exitOperation,
    addOperation,
    getOperation,
    containsOperation,
    deleteOperation,
};

char* ERROR_NAMES[3] =
{
    "OK",
    "MEMORY ERROR",
    "NULL POINTER ERROR",
};

int finish(Tree** const tree, const int errorCode)
{
    deleteTree(tree);
    printf("%s\n", ERROR_NAMES[errorCode]);
    return errorCode;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    Tree* tree = createTree();
    if (tree == NULL)
    {
        return memoryError;
    }
    char* key = "";
    char* value = "";
    bool contain = false;
    while (true)
    {
        printf("Enter 0 to exit\nEnter 1 to add element\nEnter 2 to get value by key\nEnter 3 to check if key in the dictionary\
\nEnter 4 to delete key with his value from the dictionary\n");
        int operation = 0;
        scanf_s("%d", &operation);
        readLine(0);
        switch (operation)
        {
        case exitOperation:
            deleteTree(tree);
            return ok;
        case addOperation:
            printf("Enter the key:\n");
            key = readLine(&errorCode);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            printf("Enter the value:\n");
            value = readLine(&errorCode);
            if (errorCode != ok)
            {
                free(key);
                return finish(&tree, errorCode);
            }
            errorCode = insert(tree, value, key);
            free(value);
            free(key);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            break;
        case getOperation:
            printf("Enter the key:\n");
            key = readLine(&errorCode);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            value = getValue(tree, key);
            free(key);
            if (value == NULL)
            {
                printf("No such value\n");
                break;
            }
            printf("Value - %s\n", value);
            break;
        case containsOperation:
            printf("Enter the key:");
            key = readLine(&errorCode);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            contain = isContains(tree, key);
            free(key);
            printf("%s\n", (contain ? "Contained" : "Not contained"));
            break;
        case deleteOperation:
            printf("Enter the key:");
            char* key = readLine(&errorCode);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            errorCode = deleteElement(tree, key);
            free(key);
            if (errorCode != ok)
            {
                return finish(&tree, memoryError);
            }
            printf("Deleted\n");
            break;
        default:
            printf("Invalid number of operation, try again\n");
        }
    }
    return ok;
}
