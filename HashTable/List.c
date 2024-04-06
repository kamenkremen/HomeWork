#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "List.h"
#include "ErrorCodes.h"

typedef struct ListElement
{
    struct ListElement* next;
    ListValue value;
    size_t amount;

} ListElement;

struct List
{
    size_t size;
    ListElement* head;
};

List* createList(void)
{
    return calloc(1, sizeof(List));
}

void printList(const List* const list)
{

    ListElement* current = list->head;
    for (; current != NULL; current = current->next)
    {
        printf("Word %s amount of accurances - %zu\n", current->value, current->amount);
    }
}

void deleteList(List** const list)
{
    while ((*list)->head != NULL)
    {
        ListElement* nextElement = (*list)->head->next;
        free((*list)->head->value);
        free((*list)->head);
        (*list)->head = nextElement;
    }
    free(*list);
}

bool isEmpty(const List* const list)
{
    return (list->head == NULL);
}

bool isContains(const List* const list, ListValue value)
{
    ListElement* current = list->head;
    for (; current != NULL && strcmp(current->value, value) != 0; current = current->next);
    return current != NULL;
}

ListError addWord(List* const list, ListValue value)
{
    if (list == NULL)
    {
        return nullPointerError;
    }
    ListElement* current = list->head;
    ListElement* previous = NULL;
    for (; current != NULL && strcmp(current->value, value) != 0; previous = current, current = current->next);
    if (current == NULL)
    {
        ListElement* newElement = calloc(1, sizeof(ListElement));
        if (newElement == NULL)
        {
            return memoryError;
        }
        newElement->value = value;
        newElement->amount = 1;
        if (previous == NULL)
        {
            list->head = newElement;
        }
        else
        {
            previous->next = newElement;
        }
        ++list->size;
    }
    else
    {
        ++current->amount;
        free(value);
    }
    return ok;
}

size_t getSize(const List* const list)
{
    return list->size;
}
