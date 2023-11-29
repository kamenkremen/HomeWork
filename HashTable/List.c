#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct ListElement
{
	struct ListElement* next;
	listValue value;
	size_t amount;

} ListElement;

struct List
{
	size_t size;
	ListElement* head;
};

List* createList(void)
{
	return calloc(1, sizeof(List));
}

int addElement(List* const list, const char* const value)
{

	ListElement* current = list->head;
	ListElement* newElement = calloc(1, sizeof(ListElement));
	newElement->value = value;
	newElement->amount = 1;
	if (newElement == NULL)
	{
		return memoryError;
	}
	if (current == NULL)
	{
		list->head = newElement;
		list->size = 1;
		return ok;
	}
	for (; current->next != NULL; current = current->next);
	current->next = newElement;
	++list->size;
	return ok;
}

void printList(const List* const list)
{

	ListElement* current = list->head;
	for (; current != NULL; current = current->next)
	{

		printf("Word %s amount of accurances - %u\n", current->value, current->amount);
	}
}

listValue getValueByIndex(const List* const list, const size_t index, int* const errorCode)
{
	if (list == NULL)
	{
		*errorCode = nullPointerError;
		return nullPointerError;
	}
	ListElement* current = list->head;
	if (current == NULL)
	{
		*errorCode = noSuchElement;
		return noSuchElement;
	}
	for (size_t i = 0; (i < index) && (current != NULL); ++i)
	{
		current = current->next;
	}
	if (current == NULL)
	{
		*errorCode = noSuchElement;
		return noSuchElement;
	}
	return current->value;
}

void deleteList(List** const list)
{
	while ((*list)->head != NULL)
	{
		ListElement* nextElement = (*list)->head->next;
		free((*list)->head);
		(*list)->head = nextElement;
	}
	free(*list);
}

bool isEmpty(const List* const list)
{
	return (list->head == NULL);
}

bool isContains(const List* const list, const char value[])
{
	ListElement* current = list->head;
	for (; current != NULL && strcmp(current->value, value) != 0; current = current->next);
	return (current == NULL ? false : strcmp(current->value, value) == 0);
}

int addWord(List* const list, const char* value)
{
	if (list == NULL)
	{
		return nullPointerError;
	}
	ListElement* current = list->head;
	for (; current != NULL && strcmp(current->value, value) != 0; current = current->next);
	if (current == NULL)
	{
		return addElement(list, value);
	}
	++current->amount;
	return ok;
}

size_t getSize(const List* const list)
{
	return list->size;
}
