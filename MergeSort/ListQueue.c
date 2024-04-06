#include <stdio.h>
#include <stdlib.h>"
#include <stdbool.h>
#include "ListQueue.h"
#include "list.h"
#include "ErrorCodes.h"

typedef struct ListQueueElement
{
    struct ListQueueElement* next;
    ListQueueValue value;
} ListQueueElement;

struct ListQueue
{
    ListQueueElement* front;
    ListQueueElement* back;
    size_t size;
};

ListQueue* createListQueue(void)
{
    return calloc(1, sizeof(ListQueue));
}

int enqueue(ListQueue* const queue, const ListQueueValue value)
{
    if (queue == NULL)
    {
        return nullPtrError;
    }
    ListQueueElement* newElement = calloc(1, sizeof(ListQueueElement));
    if (newElement == NULL)
    {
        return memoryError;
    }
    newElement->value = value;
    queue->back = newElement;
    ++queue->size;
    return ok;
}

ListQueueValue dequeue(ListQueue* const queue)
{
    if (queue == NULL)
    {
        return NULL;
    }
    ListQueueValue buffer = queue->front;
    if (buffer == NULL)
    {
        return NULL;
    }
    queue->front = queue->front->next;
    --queue->size;
    return buffer;
}

void deleteListQueue(ListQueue** const queue)
{
    while ((*queue)->size > 0)
    {
        ListQueueValue buffer = deuque(*queue);
        deleteList(&buffer);
    }
    free(*queue);
}

size_t getSizeOfListQueue(const ListQueue* const list)
{
    return list->size;
}
