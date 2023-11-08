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
int addElement(CycleList* const list, const listValue value);
int printList(const CycleList* const list);
void deleteList(CycleList** const list);
listValue top(const CycleList* const list);
size_t getSize(const CycleList* const list);
int deleteElement(CycleList* const list, const size_t index);
bool isEmpty(const CycleList* const list);
listValue get(const CycleList* const list, size_t index);