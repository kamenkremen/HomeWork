#include <stdio.h>
#include <stdlib.h>"
#include <stdbool.h>
#include "list.h"
#include "ErrorCodes.h"

typedef struct ListElement
{
    struct ListElement* next;
    ListValue value;
} ListElement;

struct List
{
    ListElement* head;
    size_t size;
};

List* createList(void)
{
    return calloc(1, sizeof(List));
}

int addElement(List* const list, const ListValue value)
{
    ListElement* current = list->head;
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return memoryError;
    }
    newElement->value = value;
    if (current == NULL)
    {
        list->head = newElement;
        ++list->size;
        return ok;
    }
    
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newElement;
    ++list->size;
    return ok;
}

int deleteElement(List* const list, const size_t index)
{
    if (index >= list->size)
    {
        return noSuchElement;
    }
    ListElement* current = list->head;
    if (current == NULL)
    {
        return nullPtrError;
    }
    if (index == 0)
    {
        list->head = current->next;
        --list->size;
        free(current);
        return ok;
    }
    size_t currentIndex = 0;
    for (size_t i = 0; i < index - 1; ++i)
    {
        current = current->next;
    }
    current->next = current->next->next;
    free(current->next);
    --list->size;
    return ok;
}

void deleteList(List** const list)
{
    if (list == NULL || *list == NULL)
    {
        return;
    }
    while ((*list)->size > 0)
    {
        deleteElement(*list, 0);
    }
    free(*list);
}

size_t getSize(const List* const list)
{
    return list->size;
}

bool isEmpty(const List* const list)
{
    return list->head == NULL;
}

ListValue getElement(const List* const list, const size_t index, int* errorCode)
{
    if (index >= list->size)
    {
        *errorCode = noSuchElement;
        return;
    }
    ListElement* current = list->head;
    if (current == NULL)
    {
        *errorCode = nullPtrError;
        return;
    }
    for (size_t i = 0; i < index; ++i)
    {
        current = current->next;
    }
    return current->value;
}

int moveHead(List* const source, List* const destination)
{
    if (source == NULL || destination == NULL || source->head == NULL)
    {
        return nullPtrError;
    }
    ListElement* head = source->head;
    source->head = source->head->next;
    --source->size;
    head->next = destination->head;
    destination->head = head->next;
    ++destination->size;
    return ok;
}
