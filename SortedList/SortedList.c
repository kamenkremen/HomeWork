#include "SortedList.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement
{
    struct ListElement* next;
    listValue value;

} ListElement;

struct SortedList
{
    ListElement* head;
};

SortedList* createList(void)
{
    return (SortedList*)calloc(1, sizeof(SortedList));
}

errorCodeForList addElement(SortedList* const list, const listValue value)
{
    ListElement* current = list->head;
    ListElement* newElement = (ListElement*)calloc(1, sizeof(ListElement));
    newElement->value = value;
    if (newElement == NULL)
    {
        return listMemoryError;
    }
    if (current == NULL)
    {
        list->head = newElement;
        return listOk;
    }
    if (current->value >= value)
    {
        list->head = newElement;
        newElement->next = current;
        return listOk;
    }
    for (; current->next != NULL && current->next->value < value; current = current->next);
    newElement->next = current->next;
    current->next = newElement;
    return listOk;
}

bool deleteElement(SortedList* const list, const listValue value)
{
    if (list->head == NULL)
    {
        return true;
    }
    ListElement* current = list->head;
    ListElement* previous = NULL;
    for (; current != NULL && current->value != value; previous = current, current = current->next);
    if (current == NULL)
    {
        return true;
    }
    if (previous != NULL)
    {
        previous->next = current->next;
    }
    else
    {
        list->head = current->next;
    }
    free(current);
    return false;
}

errorCodeForList printList(const SortedList* const list)
{
    ListElement* current = list->head;
    for (; current != NULL; current = current->next)
    {
        printf("%d ", current->value);
    }
    printf("\n");
    return listOk;
}

void deleteList(SortedList** const list)
{
    while ((*list)->head != NULL)
    {
        deleteElement(*list, (*list)->head->value);
    }
    free(*list);
}

bool isEmpty(const SortedList* const list)
{
    return (list->head == NULL);
}

listValue top(const SortedList* const list, int* const errorCode)
{
    if (list->head == NULL)
    {
        *errorCode = listNullPointerError;
        return listNullPointerError;
    }
    return list->head->value;
}
