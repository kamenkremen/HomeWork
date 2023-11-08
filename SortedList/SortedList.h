#pragma once
#include <stdbool.h>
enum ERRORCODES_FOR_LIST
{
	listOk,
	listMemoryError,
	listNoSuchElement,
	listNullPointerError,
};
typedef int listValue;
typedef struct SortedList SortedList;
SortedList* createList(void);
int addElement(SortedList* const list, const listValue value);
int deleteElement(SortedList* const list, const listValue value);
int printList(const SortedList* const list);
void deleteList(SortedList** const list);
listValue top(const SortedList* const list);
bool isEmpty(SortedList* list);