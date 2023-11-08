#pragma once
#include <stdbool.h>
#include "list.h"
typedef List* ListOfListsValue;
typedef struct ListOfLists ListOfLists;
ListOfLists* createListOfLists(void);
int addList(ListOfLists* const list, const ListOfListsValue value);
void deleteListOfLists(ListOfLists** const list);
size_t getSizeOfListOfLists(const ListOfLists* const list);
int deleteListFromListOfLists(ListOfLists* const list, const size_t index);
bool isListOfListsEmpty(const ListOfLists* const list);
ListOfListsValue getList(const ListOfLists* const list, const size_t index, int* errorCode);