#include <stdlib.h>
#include "Stack.h"

struct Stack
{
	StackValue value;
	struct Stack* previous;
};

int push(Stack** head, const StackValue value)
{
	Stack* next = malloc(sizeof(Stack));
	if (next == NULL)
	{
		return stackMemoryError;
	}
	next->value = value;
	next->previous = *head;
	*head = next;
	return stackOk;
}

int pop(Stack** head)
{
	if (isEmpty(*head))
	{
		return stackNullPointerError;
	}
	Stack* trash = *head;
	*head = (*head)->previous;
	free(trash);
	return stackOk;
}

StackValue top(Stack* head, int* errorCode)
{
	if (isEmpty(head))
	{
		*errorCode = stackNullPointerError;
		return stackNullPointerError;
	}
	return head->value;
}

int freeStack(Stack** head)
{
	while (!isEmpty(*head))
	{
		pop(head);
	}
	return stackOk;
}

int isEmpty(Stack* stack)
{
	return stack == NULL;
}