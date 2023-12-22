#pragma once

#include <stdbool.h>

// type of the queue errors
typedef int QueueErrorType;
//type of the queue values
typedef int QueueValueType;
// ADT queue
typedef struct Queue Queue;
// returns empty queue
Queue* createQueue(void);
// add element to the back of the queue
QueueErrorType enqueue(Queue* const queue, const QueueValueType value);
// deletes value from the front of queue
QueueErrorType dequeue(Queue* const queue);
//returns the value form the front of the queue
QueueValueType front(Queue* const queue, QueueErrorType* const errorCode);
// returns true if queue is empty
bool isEmpty(Queue* const queue);
// deletes queue
void deleteQueue(Queue** const queue);
