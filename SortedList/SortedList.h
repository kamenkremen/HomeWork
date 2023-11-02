#pragma once
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
int addElement(SortedList* list, const listValue value);
int deleteElement(SortedList* list, const listValue value);
int printList(SortedList* list);
void deleteList(SortedList** list);
listValue top(SortedList* list);