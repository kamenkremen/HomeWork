#pragma once

#include <stdlib.h>

#define DEFAULT_QUEUE_VALUE 0

// type of value contained in queue
typedef int QueueValue;

// type of priority contained in queue
typedef int QueuePriority;

// type of error codes that queue returns
typedef int QueueErrorCode;

// priority queue
typedef struct PriorityQueue PriorityQueue;

// insert element in the queue
QueueErrorCode insert(PriorityQueue* const queue, const QueueValue value, const QueuePriority priority);

// returns element with the lowest priority and deletes it
QueueValue pop(PriorityQueue* const queue, QueuePriority* const priority, QueueErrorCode* const errorCode);

// returns new priority queue
PriorityQueue* createPriorityQueue(void);

// returns size of queue
size_t getSize(const PriorityQueue* const queue);

// deletes queue
void deleteQueue(PriorityQueue** const queue);
