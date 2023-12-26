#include "MergeSort.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "ListQueue.h"
#include <string.h>
#include "ErrorCodes.h"

static List* merge(const List* const first, const List* const second, const bool sortByName, int* const errorCode)
{
    List* newList = createList();
    if (newList == NULL)
    {
        *errorCode = memoryError;
        return NULL;
    }
    size_t i = 0;
    size_t j = 0;
    while (getSize(first) + getSize(second) > 0)
    {
        ListValue firstValue = getElement(first, 0, errorCode);
        if (*errorCode != ok)
        {
            deleteList(&newList);
            return;
        }
        ListValue secondValue = getElement(second, 0, errorCode);
        if (*errorCode != ok)
        {
            deleteList(&newList);
            return;
        }
        char* firstValueToSort = (sortByName ? firstValue.name : firstValue.number);
        char* secondValueToSort = (sortByName ? secondValue.name : secondValue.number);
        bool comparator = false;
        if (getSize(first) > 0 && getSize(second) > 0)
        {
            comparator = strcmp(firstValueToSort, secondValueToSort) < 0;
        }
        else if (getSize(first) == 0)
        {
            comparator = true;
        }
        else
        {
            comparator = false;
        }
        *errorCode = moveHead(comparator ? second : first, newList);
        if (*errorCode)
        {
            deleteList(&newList);
            return NULL;
        }
    }
    return newList;
}

static void sort(ListQueue* const list, const bool sortByName, int* mainErrorCode)
{
    int errorCode = 0;
    while (getSizeOfListQueue(list) > 1)
    {
        List* firstList = getList(list, 0, &errorCode);
        if (errorCode != ok)
        {
            *mainErrorCode = errorCode;
            return;
        }
        List* secondList = getList(list, 1, &errorCode);
        if (errorCode != ok)
        {
            *mainErrorCode = errorCode;
            return;
        }
        dequeue(queue);
        dequeue(queue);
        List* newList = merge(firstList, secondList, sortByName, &errorCode);
        if (errorCode != ok)
        {
            deleteList(&newList);
            *mainErrorCode = errorCode;
            return;
        }
        if (addList(list, newList) != ok)
        {
            deleteList(&newList);
            *mainErrorCode = memoryError;
            return;
        }
    }
}

void mergeSort(List** const list, const bool sortByName, int* mainErrorCode)
{
    ListQueue* ListQueue = createListQueue();
    if (ListQueue == NULL)
    {
        return memoryError;
    }
    int errorCode = 0;
    for (size_t i = 0; i < getSize(*list); ++i)
    {
        List* listElement = createList();
        if (listElement == NULL)
        {
            return memoryError;
        }
        ListValue value = getElement(*list, i, &errorCode);
        if (errorCode != ok)
        {
            return errorCode;
        }
        addElement(listElement, value);
        addList(ListQueue, listElement);
    }

    sort(ListQueue, sortByName, &errorCode);
    if (errorCode != ok)
    {
        *mainErrorCode = errorCode;
        return;
    }
    *list = getList(ListQueue, 0, &errorCode);
    if (errorCode != ok)
    {
        *list = NULL;
        *mainErrorCode = errorCode;
        return;
    }
}
