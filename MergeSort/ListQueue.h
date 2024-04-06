#pragma once

#include <stdbool.h>

#include "list.h"

typedef List* ListQueueValue;

typedef struct ListQueue ListQueue;

ListQueue* createListQueue(void);

int enqueue(ListQueue* const queue, const ListQueueValue value);

void deleteListQueue(ListQueue** const queue);

size_t getSizeOfListQueue(const ListQueue* const queue);

ListQueueValue dequeue(ListQueue* const list);

