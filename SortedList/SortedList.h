#pragma once
#include <stdbool.h>
enum ErrorCodesForList
{
    listOk,
    listMemoryError,
    listNoSuchElement,
    listNullPointerError,
};

typedef int errorCodeForList;
typedef int listValue;
typedef struct SortedList SortedList;
SortedList* createList(void);
errorCodeForList addElement(SortedList* const list, const listValue value);
bool deleteElement(SortedList* const list, const listValue value);
errorCodeForList printList(const SortedList* const list);
void deleteList(SortedList** const list);
listValue top(const SortedList* const list, int* const errorCode);
bool isEmpty(const SortedList* const list);
