#include <stdio.h>
#include <stdlib.h>
#include "SortedList.h"
#include "Test.h"

int finish(SortedList** list, const int errorCode)
{
    deleteList(list);
    return errorCode;
}

enum Operations
{
    exitOperation,
    addOperation,
    deleteOperation,
    printOperation,
};

int main(void)
{
    const int errorCode = test();
    if (errorCode != ok)
    {
        printf("ERROR IN SORTED LIST TEST, CASE %d\n", errorCode);
        return errorCode;
    }
    SortedList* list = createList();
    if (list == NULL)
    {
        printf("MEMORY ERROR\n");
        return memoryError;
    }
    while (true)
    {
        printf("Enter number of the operation:\n0 - exit\n1 - add element to the list\
\n2 - delete element from the list\n3 - print list\n");
        const int operation = 0;
        if (scanf_s("%d", &operation) != 1)
        {
            printf("INPUT ERROR\n");
            return finish(&list, inputError);
        }
        int value = 0;
        int errorCode = 0;
        switch (operation)
        {
            case exitOperation:
                return finish(&list, ok);
            case addOperation:
                printf("Enter value to add:\n");
                if (scanf_s("%d", &value) != 1)
                {
                    printf("INPUT ERROR\n");
                    return finish(&list, inputError);
                }
                errorCode = addElement(list, value);
                if (errorCode != ok)
                {
                    printf("MEMORY ERROR\n");
                    return finish(&list, memoryError);
                }
                break;
            case deleteOperation:
                printf("Enter value to remove:\n");
                if (scanf_s("%d", &value) != 1)
                {
                    printf("INPUT ERROR\n");
                    return finish(&list, inputError);
                }
                if (deleteElement(list, value))
                {
                    printf("No element has been removed\n");
                    continue;
                }
                break;
            case printOperation:
                printList(list);
                break;
            default:
                printf("Enter value between 0 and 3.\n");
        }
    }
    return ok;
}
