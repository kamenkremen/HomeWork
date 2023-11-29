#pragma once

#include <stdbool.h>
#include "ErrorCodes.h"

// list contains this type of value
typedef char* listValue;
//list.
typedef struct List List;
//create list.
List* createList(void);
//get value by index in list, indexes starts with 0
listValue getValueByIndex(const List* const list, const size_t index, int* const errorCode);
//add element in the end of the list
int addElement(List* const list, const char* const value);
//print list
void printList(const List* const list);
//delete list
void deleteList(List** const list);
//check if list empty
bool isEmpty(List* list);
//check if value in list
bool isContains(const List* const list, const char* value);
//add word
int addWord(const List* const list, const char* value);
//returns amount of elements
size_t getSize(const List* const list);
