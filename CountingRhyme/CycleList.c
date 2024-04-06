#include <stdlib.h>
#include <stdbool.h>

#include "CycleList.h"
#include "ErrorCodes.h"

typedef struct ListElement
{
    struct ListElement* next;
    struct ListElement* previous;
    listValue value;

} ListElement;

struct CycleList
{
    ListElement* head;
    size_t size;
};

struct Position
{
    ListElement* element;
};

CycleList* createList(void)
{
    return calloc(1, sizeof(CycleList));
}

bool addElement(CycleList* const list, const listValue value)
{
    ListElement* newElement = calloc(1, sizeof(ListElement));
    if (newElement == NULL)
    {
        return true;
    }
    newElement->value = value;
    if (list->head == NULL)
    {
        newElement->next = newElement;
        newElement->previous = newElement;
        list->head = newElement;
        ++list->size;
        return false;
    }
    ListElement* current = list->head->previous;
    newElement->next = list->head;
    newElement->previous = current;
    current->next = newElement;
    list->head->previous = newElement;
    ++list->size;
    return false;
}

Position* getStartPosition(const CycleList* const list)
{
    if (list == NULL)
    {
        return NULL;
    }
    Position* position = (Position*)calloc(1, sizeof(Position));
    if (position == NULL)
    {
        return NULL;
    }
    position->element = list->head;
    return position;
}

bool movePostionForward(Position* const position)
{
    if (position == NULL || position->element == NULL)
    {
        return true;
    }
    position->element = position->element->next;
    return false;
}

void deletePosition(Position** const position)
{
    if (position == NULL)
    {
        return;
    }
    free(*position);
}

bool deleteElement(CycleList* const list, const Position* const position)
{
    if (list->head == NULL || position == NULL)
    {
        return true;
    }
    if (list->size == 1)
    {
        free(list->head);
        --list->size;
        return false;
    }
    ListElement* element = position->element;
    element->previous->next = element->next;
    element->next->previous = element->previous;
    list->head = element->next;
    --list->size;
    free(element);
    return false;
}

void deleteList(CycleList** const list)
{
    if (list == NULL || *list == NULL)
    {
        return;
    }
    if ((*list)->size != 0)
    {
        ListElement* current = (*list)->head->next;
        for (; current != (*list)->head; current = current->next)
        {
            free(current->previous);
        }
        free((*list)->head);
    }
    free(*list);
}

listValue top(const CycleList* const list, int* const errorCode)
{
    if (list->head == NULL)
    {
        *errorCode = nullPointerError;
        return 1;
    }
    return list->head->value;
}

size_t getSize(const CycleList* const list)
{
    return list->size;
}
