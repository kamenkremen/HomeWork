#pragma once
#include <stdlib.h>

// type of value contained in queue
typedef int QueueValue;

// type of priority contained in queue
typedef int QueuePriority;

// type of error codes that queue returns
typedef int QueueErrorCode;

// queue with priorities
typedef struct PriorityQueue PriorityQueue;

// insert element in the queue
QueueErrorCode enqueue(PriorityQueue* const queue, const QueueValue value, const QueuePriority priority);

// returns element with the lowest priority and deletes it
QueueValue dequeue(PriorityQueue* const queue, QueueErrorCode* const errorCode);

// returns new priority queue
PriorityQueue* createPriorityQueue(void);

// deletes queue
void deleteQueue(PriorityQueue** const queue);
