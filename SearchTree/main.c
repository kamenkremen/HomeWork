#include <stdio.h>
#include <stdlib.h>

#include "SearchTree.h"
#include "Test.h"
#include "Strings.h"

#define COMMANDS "Enter 0 to exit the programm.\nEnter 1 to add element.\n\
Enter 2 to get the value of the key.\n\
Enter 3 to check if dictionary is containing the key.\n\
Enter 4 to delete the key and the value from the dictionary.\n"

char* ERRORNAMES[5] = {
    "",
    "Memory error",
    "Null pointer error",
    "No such element",
    "Input error",
};

enum Operations
{
    exitOperation,
    addOperation,
    getOperation,
    containOperation,
    deleteOperation,
};

int finish(Tree** const tree, const int errorCode)
{
    printf("%s\n", ERRORNAMES[errorCode]);
    deleteTree(tree);
    return errorCode;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode)
    {
        return testError;
    }
    Tree* tree = createTree();

    while (true)
    {
        printf(COMMANDS);
        int operation = 0;
        if (scanf_s("%d", &operation) != 1)
        {
            printf("Incorrect input, enter the number from 1 to 4.\n");
            continue;
        }
        int key = 0;
        int errorCode = ok;
        switch (operation)
        {
        case exitOperation:
            return finish(&tree, 0);
        case addOperation:
            printf("Enter the key and the value\n");
            char* value = "";
            if (scanf_s("%d", &key) != 1)
            {
                return finish(&tree, inputError);
            }
            getc(stdin);
            value = readLine();
            if (value == NULL)
            {
                return finish(&tree, inputError);
            }
            errorCode = add(tree, key, value);
            free(value);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            printf("Element added\n");
            break;
        case getOperation:
            printf("Enter the key\n");
            if (scanf_s("%d", &key) != 1)
            {
                return finish(&tree, inputError);
            }
            errorCode = ok;
            const char* outputValue = get(tree, key, &errorCode);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            if (outputValue == NULL)
            {
                printf("No such value\n");
                break;
            }
            printf("Value: %s\n", outputValue);
            break;
        case containOperation:
            printf("Enter the key\n");
            if (scanf_s("%d", &key) != 1)
            {
                return finish(&tree, inputError);
            }
            errorCode = ok;
            const bool containing = contains(tree, key, &errorCode);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            printf("%s\n", containing ? "This key in dictionary" : "This key is not in dictionary");
            break;
        case deleteOperation:
            printf("Enter the key\n");
            if (scanf_s("%d", &key) != 1)
            {
                return finish(&tree, inputError);
            }
            errorCode = delete(tree, key);
            if (errorCode != ok)
            {
                return finish(&tree, errorCode);
            }
            break;
        default:
            printf("Incorrect input, enter the number from 1 to 4.\n");
        }
    }
    return ok;
}
