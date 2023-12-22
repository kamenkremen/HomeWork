#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Queue.h"
#include "ErrorCodes.h"

typedef struct QueueElement
{
    int value;
    struct QueueElement* next;
} QueueElement;

struct Queue
{
    QueueElement* head;
    QueueElement* back;
};

Queue* createQueue(void)
{
    return calloc(1, sizeof(Queue));
}

QueueErrorType enqueue(Queue* const queue, const QueueValueType value)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }
    QueueElement* newQueueElement = calloc(1, sizeof(QueueElement));
    if (newQueueElement == NULL)
    {
        return memoryError;
    }
    newQueueElement->value = value;
    if (isEmpty(queue))
    {
        queue->head = newQueueElement;
    }
    else
    {
        (queue->back)->next = newQueueElement;
    }
    queue->back = newQueueElement;
    return ok;
}

QueueErrorType dequeue(Queue* const queue)
{
    if (queue == NULL)
    {
        return nullPointerError;
    }
    if (isEmpty(queue))
    {
        return emptyQueueError;
    }
    QueueElement* queueElementToDequeue = queue->head;
    queue->head = (queue->head)->next;
    free(queueElementToDequeue);
    if (isEmpty(queue))
    {
        queue->back = NULL;
    }
    return ok;
}

bool isEmpty(const Queue* const queue)
{
    return queue == NULL || queue->head == NULL;
}

QueueValueType front(const Queue* const queue, QueueErrorType* const errorCode)
{
    if (queue == NULL)
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    if (queue->head == NULL)
    {
        *errorCode = emptyQueueError;
        return NULL;
    }
    return (queue->head)->value;
}

void deleteQueue(Queue** const queue)
{
    if (queue == NULL || *queue == NULL)
    {
        return;
    }
    while (!isEmpty(*queue))
    {
        dequeue(*queue);
    }
    free(*queue);
}
