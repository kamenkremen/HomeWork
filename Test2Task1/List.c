#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct ListElement
{
	struct ListElement* next;
	listValue value;

} ListElement;

struct Position
{
	ListElement* position;
};

struct List
{
	ListElement* head;
};

List* createList(void)
{
	return calloc(1, sizeof(List));
}

int addElement(List* const list, const listValue value)
{
	ListElement* current = list->head;
	ListElement* newElement = calloc(1, sizeof(ListElement));
	newElement->value = value;
	if (newElement == NULL)
	{
		return memoryError;
	}
	if (current == NULL)
	{
		list->head = newElement;
		return ok;
	}
	for (; current->next != NULL; current = current->next);
	current->next = newElement;
	return ok;
}

int deleteNextElement(Position* const position)
{
	if (position == NULL)
	{
		return nullPointerError;
	}
	if (position->position->next == NULL)
	{
		return noSuchElement;
	}
	ListElement* next = position->position->next->next;
	free(position->position->next);
	position->position->next = next;
	return ok;
}

Position* getStartPosition(const List* const list)
{
	if (list == NULL)
	{
		return NULL;
	}
	Position* position = (Position*)calloc(1, sizeof(Position));
	if (position == NULL)
	{
		return position;
	}
	position->position = list->head;
	return position;
}

int nextPosition(Position** const position)
{
	if (position == NULL)
	{
		return nullPointerError;
	}
	Position* newPosition = (Position*)calloc(1, sizeof(Position));
	if (newPosition == NULL)
	{
		return memoryError;
	}
	newPosition->position = (*position)->position->next;
	*position = newPosition;
	return ok;
}

int printList(const List* const list)
{
	ListElement* current = list->head;
	for (; current != NULL; current = current->next)
	{
		printf("%d ", current->value);
	}
	printf("\n");
	return ok;
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
