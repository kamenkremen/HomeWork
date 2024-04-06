#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct ListValue
{
    char* number;
    char* name;
} ListValue;

typedef struct List List;

List* createList(void);

int addElement(List* list, const ListValue value);

int printList(List* list);

void deleteList(List** list);

size_t getSize(List* list);

int deleteElement(List* list, const size_t index);

bool isEmpty(List* list);

ListValue getElement(List* list, size_t index, int* errorCode);

int moveHead(List* const source, List* const destination);
