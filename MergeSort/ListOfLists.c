#include <stdio.h>
#include <stdlib.h>"
#include <stdbool.h>
#include "ListOfLists.h"
#include "list.h"
#include "ErrorCodes.h"

typedef struct ListOfListsElement
{
	struct ListOfListsElement* next;
	ListOfListsValue value;
} ListOfListsElement;

struct ListOfLists
{
	ListOfListsElement* head;
	size_t size;
};

ListOfLists* createListOfLists(void)
{
	return calloc(1, sizeof(ListOfLists));
}

int addList(ListOfLists* const list, const ListOfListsValue value)
{
	ListOfListsElement* current = list->head;
	ListOfListsElement* newElement = calloc(1, sizeof(ListOfListsElement));
	newElement->value = value;
	if (newElement == NULL)
	{
		return memoryError;
	}
	if (current == NULL)
	{
		list->head = newElement;
		++list->size;
		return ok;
	}
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = newElement;
	++list->size;
	return ok;
}

int deleteListFromListOfLists(ListOfLists* const list, const size_t index)
{
	if (index >= list->size)
	{
		return noSuchElement;
	}
	ListOfListsElement* current = list->head;
	if (current == NULL)
	{
		return nullPtrError;
	}
	if (index == 0)
	{
		list->head = current->next;
		--list->size;
		free(current);
		return ok;
	}
	size_t currentIndex = 0;
	for (size_t i = 0; i < index - 1; ++i)
	{
		current = current->next;
	}
	current->next = current->next->next;
	free(current->next);
	--list->size;
	return ok;
}

void deleteListOfLists(ListOfLists** const list)
{
	while ((*list)->size > 0)
	{
		deleteListFromListOfLists(*list, 0);
	}
	free(*list);
}

size_t getSizeOfListOfLists(const ListOfLists* const list)
{
	return list->size;
}

bool isListOfListsEmpty(const ListOfLists* const list)
{
	return list->head == NULL;
}

ListOfListsValue getList(const ListOfLists* const list, const size_t index, int *errorCode)
{
	if (index >= list->size)
	{
		*errorCode = noSuchElement;
		return;
	}
	ListOfListsElement* current = list->head;
	for (size_t i = 0; i < index; ++i)
	{
		current = current->next;
	}
	return current->value;
}