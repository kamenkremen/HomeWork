#include "SortedList.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListElement
{
	struct ListElement* next;
	listValue value;

} ListElement;

struct SortedList
{
	ListElement* head;
};

SortedList* createList(void)
{
	return calloc(1, sizeof(SortedList));
}

int addElement(SortedList* const list, const listValue value)
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
		list->head = newElement;
		return listOk;
	}
	if (current->value >= value)
	{
		list->head = newElement;
		newElement->next = current;
		return listOk;
	}
	while (current->next != NULL && current->next->value < value)
	{
		current = current->next;
	}
	newElement->next = current->next;
	current->next = newElement;
	return listOk;
}

int deleteElement(SortedList* const list, const listValue value)
{
	ListElement* current = list->head;
	ListElement* newElement = calloc(1, sizeof(ListElement));
	ListElement* previous = NULL;
	while (current->value != value)
	{
		previous = current;
		current = current->next;
		if (current == NULL)
		{
			return listNoSuchElement;
		}
	}
	if (previous != NULL)
	{
		previous->next = current->next;
	}
	else
	{
		list->head = current->next;
	}
	free(current);
	return listOk;
}

int printList(const SortedList* const list)
{
	ListElement* current = list->head;
	while (current != NULL)
	{
		printf("%d ", current->value);
		current = current->next;
	}
	printf("\n");
	return listOk;
}

void deleteList(SortedList** const list)
{
	while ((*list)->head != NULL)
	{
		deleteElement(*list, (*list)->head->value);
	}
	free(*list);
}

bool isEmpty(const SortedList* const list)
{
	return (list->head == NULL);
}

listValue top(const SortedList* const list)
{
	if (list->head == NULL)
	{
		return listNullPointerError;
	}
	return list->head->value;
}