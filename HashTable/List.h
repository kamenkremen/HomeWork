#pragma once

#include <stdbool.h>

// list errors
typedef int ListError;
// list contains this type of value
typedef const char* ListValue;
// list
typedef struct List List;
// create list
List* createList(void);
// print list
void printList(const List* const list);
// delete list
void deleteList(List** const list);
// check if list empty
bool isEmpty(List* list);
// check if value in list
bool isContains(const List* const list, ListValue value);
// add word
ListError addWord(const List* const list, ListValue value);
// returns amount of elements
size_t getSize(const List* const list);
