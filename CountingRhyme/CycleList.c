#include "CycleList.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement
{
	struct ListElement* next;
	listValue value;

} ListElement;

struct CycleList
{
	ListElement* head;
	size_t size;
};

CycleList* createList(void)
{
	return calloc(1, sizeof(CycleList));
}

int addElement(CycleList* const list, const listValue value)
{
	ListElement* current = list->head;
	ListElement* newElement = calloc(1, sizeof(ListElement));
	newElement->value = value;
	if (newElement == NULL)
	{
		return listMemoryError;
	}
	if (current == NULL)
	{
		newElement->next = newElement;
		list->head = newElement;
		++list->size;
		return listOk;
	}
	while (current->next != list->head)
	{
		current = current->next;
	}
	newElement->next = list->head;
	current->next = newElement;
	++(list->size);
	return listOk;
}

int deleteElement(CycleList* const list, const size_t index)
{
	if (list->head == NULL)
	{
		return listNullPointerError;
	}
	ListElement* current = list->head;
	ListElement* previous = NULL;
	for (size_t currentIndex = 1; currentIndex < index; ++currentIndex)
	{
		previous = current;
		current = current->next;
	}
	if (current == list->head)
	{
		ListElement* lastElement = current;
		while (lastElement->next != current)
		{
			lastElement = lastElement->next;
		}
		if (current == lastElement)
		{
			free(current);
			list->size = 0;
			return listOk;
		}
		lastElement->next = current->next;
		free(current);
		list->head = lastElement->next;
		--list->size;
		return listOk;
	}
	previous->next = current->next;
	free(current);
	--list->size;
	return listOk;
}

int printList(const CycleList* const list)
{
	ListElement* current = list->head;
	while (current->next != list->head)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("%d\n", current->value);
	return listOk;
}

void deleteList(CycleList** const list)
{
	if (*list == NULL || (*list)->head == NULL)
	{
		return;
	}
	while ((*list)->size != 0)
	{
		deleteElement(*list, 1);
	}
	free(*list);
}

bool isEmpty(const CycleList* const list)
{
	return (list->head == NULL);
}

listValue top(const CycleList* const list)
{
	if (list->head == NULL)
	{
		return listNullPointerError;
	}
	return list->head->value;
}

size_t getSize(const CycleList* const list)
{
	return list->size;
}

listValue get(const CycleList* const list, size_t index)
{
	size_t currentIndex = 0;
	ListElement* current = list->head;
	index %= getSize(list);
	while (currentIndex != index)
	{
		current = current->next;
		++currentIndex;
	}
	return current->value;
}