#include <stdlib.h>
#include <stdio.h>

#include "List.h"

char* TEST_ERRORCODES[3] = {
    "",
    "LIST TEST",
    "DELETE ODD INDEXES TEST",
};

void deleteOddIndexes(List* list)
{
    if (list == NULL)
    {
        return nullPointerError;
    }
    Position* current = getStartPosition(list);
    if (current == NULL)
    {
        return;
    }
    int errorCode = ok;
    while (current != NULL)
    {
        errorCode = deleteNextElement(current);
        if (errorCode != ok)
        {
            if (errorCode == noSuchElement)
            {
                break;
            }
            return;
        }
        errorCode = nextPosition(&current);
        if (errorCode != ok && errorCode != noSuchElement)
        {
            if (errorCode == noSuchElement)
            {
                break;
            }
            return;
        }
    }
}

int listTest(void)
{
    List* list = createList();
    if (list == NULL)
    {
        return 1;
    }
    if (addElement(list, 1) != ok)
    {
        deleteList(&list);
        return 2;
    }
    if (addElement(list, 2) != ok)
    {
        deleteList(&list);
        return 3;
    }
    if (addElement(list, 3) != ok)
    {
        deleteList(&list);
        return 4;
    }
    Position* position = getStartPosition(list);
    if (position == NULL)
    {
        deleteList(&list);
        return 5;
    }
    if (deleteNextElement(position) != ok)
    {
        deleteList(&list);
        free(position);
        return 6;
    }
    int errorCode = ok;
    if (getValueByIndex(list, 1, &errorCode) != 3 || errorCode != ok)
    {
        deleteList(&list);
        free(position);
        return 7;
    }
    if (deleteNextElement(position) != ok)
    {
        deleteList(&list);
        free(position);
        return 8;
    }
    deleteList(&list);
    free(position);
    return ok;
}

int deleteOddIndexesTest(void)
{
    List* list = createList();
    if (list == NULL)
    {
        return 1;
    }
    addElement(list, 1);
    addElement(list, 2);
    addElement(list, 3);
    addElement(list, 4);
    addElement(list, 5);
    int errorCode = ok;
    deleteOddIndexes(list);
    errorCode = ok;
    if (getValueByIndex(list, 0, &errorCode) != 1 || errorCode != ok || getValueByIndex(list, 1, &errorCode) != 3 || errorCode != ok || getValueByIndex(list, 2, &errorCode) != 5 || errorCode != ok) {
        deleteList(&list);
        return 2;
    }
    deleteOddIndexes(list);
    if (getValueByIndex(list, 0, &errorCode) != 1 || errorCode != ok && getValueByIndex(list, 1, &errorCode) != 5 || errorCode != ok) {
        deleteList(&list);
        return 3;
    }
    deleteList(&list);
    return ok;
}

int tests(void)
{
    int errorCode = listTest();
    if (errorCode != ok)
    {   
        return 10 + errorCode;
    }
    errorCode = deleteOddIndexesTest();
    if (errorCode != ok)
    {
        return 20 + errorCode;
    }
    return ok;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN TEST %s, CASE %d\n", TEST_ERRORCODES[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    printf("NO ERRORS!\n");
    return ok;
}
