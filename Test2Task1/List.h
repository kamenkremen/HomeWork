#pragma once
#include <stdbool.h>
#include "ErrorCodes.h"

// list contains this type of value
typedef int listValue;
//list.
typedef struct List List;
//position of the elemnent in list, made for quick deletion
typedef struct Position Position;
//return position of the first element in list
Position* getStartPosition(const List* const list);
//moves position to the next element
int nextPosition(Position** const position);
//delete element, what next to the element in position
int deleteNextElement(Position* const position);
//create list.
List* createList(void);
//get value by index in list, indexes starts with 0
listValue getValueByIndex(const List* const list, const size_t index, int* const errorCode);
//add element in the end of the list
int addElement(List* const list, const listValue value);
//print list
int printList(const List* const list);
//delete list
void deleteList(List** const list);
//check if list empty
bool isEmpty(List* list);
