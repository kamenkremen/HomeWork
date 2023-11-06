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
typedef struct CycleList CycleList;
CycleList* createList(void);
int addElement(CycleList* list, const listValue value);
int printList(CycleList* list);
void deleteList(CycleList** list);
listValue top(CycleList* list);
size_t getSize(CycleList* list);
int deleteElement(CycleList* list, const size_t index);
bool isEmpty(CycleList* list);
listValue get(CycleList* list, size_t index);