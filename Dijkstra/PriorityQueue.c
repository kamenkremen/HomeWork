#include <stdlib.h>
#include <stdio.h>

#include "PriorityQueue.h"
#include "ErrorCodes.h"

typedef struct QueueElement
{
    QueueValue value;
    QueuePriority priority;
} QueueElement;

struct PriorityQueue
{
    QueueElement** heap;
    size_t size;
    size_t capacity;
};

static void swap(QueueElement** const first, QueueElement** const second)
{
    QueueElement* third = *first;
    *first = *second;
    *second = third;
}

static QueueErrorCode siftUp(PriorityQueue* queue, size_t index)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }
    for (; index != 0 && queue->heap[index]->priority < queue->heap[(index - 1) / 2]->priority; index = (index - 1) / 2)
    {
        swap(&queue->heap[index], &queue->heap[(index - 1) / 2]);
    }
    return ok;
}

static QueueErrorCode siftDown(PriorityQueue* queue, size_t index)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }
    while (2 * index + 1 < queue->size)
    {
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;
        size_t j = leftChild;
        if (rightChild < queue->size && queue->heap[rightChild]->priority < queue->heap[leftChild]->priority)
        {
            j = rightChild;
        }
        if (queue->heap[index]->priority <= queue->heap[j]->priority)
        {
            break;
        }
        swap(&queue->heap[index], &queue->heap[j]);
        index = j;
    }
    return ok;
}

PriorityQueue* createPriorityQueue(void)
{
    PriorityQueue* queue = (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
    if (queue == NULL)
    {
        return NULL;
    }
    queue->capacity = 1;
    queue->heap = (QueueElement**)calloc(1, sizeof(QueueElement*));
    if (queue->heap == NULL)
    {
        free(queue);
        return NULL;
    }
    return queue;
}

QueueErrorCode insert(PriorityQueue* const queue, const QueueValue value, const QueuePriority priority)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }
    if (queue->capacity < queue->size)
    {
        queue->capacity *= 2;
        QueueElement** buffer = (QueueElement**)realloc(queue->heap, queue->capacity * sizeof(QueueElement));
        if (buffer == NULL)
        {
            deleteQueue(&queue);
            return memoryError;
        }
        for (size_t i = 0; i < queue->size; ++i)
        {
            free(queue->heap[i]);
        }
        queue->heap = buffer;
    }
    QueueElement* newElement = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (newElement == NULL)
    {
        return memoryError;
    }
    newElement->value = value;
    newElement->priority = priority;
    queue->heap[queue->size] = newElement;
    siftUp(queue, queue->size);
    ++queue->size;
    return ok;
}

QueueValue pop(PriorityQueue* const queue, QueuePriority* const priority, QueueErrorCode* const errorCode)
{
    if (queue == NULL)
    {
        *errorCode = nullPointerError;
        return DEFAULT_QUEUE_VALUE;
    }
    if (queue->size == 0)
    {
        *errorCode = indexOutOfRangeError;
        return DEFAULT_QUEUE_VALUE;
    }
    QueueElement* minimum = queue->heap[0];
    *priority = minimum->priority;
    QueueValue value = minimum->value;
    free(minimum);
    queue->heap[0] = queue->heap[queue->size - 1];
    *errorCode = siftDown(queue, 0);
    --queue->size;
    return value;
}

size_t getSize(const PriorityQueue* const queue)
{
    if (queue == NULL)
    {
        return 0;
    }
    return queue->size;
}

void deleteQueue(PriorityQueue** queue)
{
    if (queue == NULL)
    {
        return;
    }
    while ((*queue)->size != 0)
    {
        QueuePriority priority = 0;
        QueueErrorCode errorCode = ok;
        pop(*queue, &priority, &errorCode);
    }
    (*queue)->heap = NULL;
    free(*queue);
}
