#include <stdlib.h>
#include <stdio.h>

#include "PriorityQueue.h"
#include"ErrorCodes.h"

int finish(PriorityQueue** const queue, const int returnValue)
{
    deleteQueue(queue);
    return returnValue;
}

static int priorityQueueTest(void)
{
    PriorityQueue* queue = createPriorityQueue();
    if (queue == NULL)
    {
        return 1;
    }
    int errorCode = ok;
    if (dequeue(queue, &errorCode) != -1 || errorCode != indexOutOfRangeError)
    {
        return finish(&queue, 12);
    }
    errorCode = enqueue(queue, 4, 1);
    if (errorCode != ok)
    {
        return finish(&queue, 2);
    }
    errorCode = enqueue(queue, 3, 2);
    if (errorCode != ok)
    {
        return finish(&queue, 2);
    }
    errorCode = enqueue(queue, 1, 3);
    if (errorCode != ok)
    {
        return finish(&queue, 3);
    }
    errorCode = enqueue(queue, 2, 3);
    if (errorCode != ok)
    {
        return finish(&queue, 4);
    }
    errorCode = enqueue(queue, 5, 1);
    if (errorCode != ok)
    {
        return finish(&queue, 5);
    }
    for (size_t i = 0; i < 5; ++i)
    {
        int result = dequeue(queue, &errorCode);
        if (errorCode != ok || result != i + 1)
        {
            return finish(&queue, 6 + i);
        }
    }
    return finish(&queue, ok);
}

int tests(void)
{
    const int errorCode = priorityQueueTest();
    if (errorCode != ok)
    {
        printf("ERROR IN PRIORITY QUEUE TESTING, CASE %d\n", errorCode);
        return errorCode;
    }
    return ok;
}
