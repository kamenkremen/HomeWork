#include <stdlib.h>

#include "Stack.h"
#include "ErrorCodes.h"

struct Stack
{
    StackValue value;
    struct Stack* previous;
};

int push(Stack** const head, const StackValue value)
{
    if (head == NULL)
    {
        return nullPointerError;
    }
    Stack* next = (Stack*)calloc(1, sizeof(Stack));
    if (next == NULL)
    {
        return memoryError;
    }
    next->value = value;
    next->previous = *head;
    *head = next;
    return ok;
}

int pop(Stack** const head)
{
    if (isEmpty(*head))
    {
        return nullPointerError;
    }
    Stack* trash = *head;
    *head = (*head)->previous;
    free(trash);
    return ok;
}

StackValue top(const Stack* const head, int* const errorCode)
{
    if (isEmpty(head))
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    return head->value;
}

void freeStack(Stack** const head)
{
    if (head == NULL)
    {
        return;
    }
    while (!isEmpty(*head))
    {
        pop(head);
    }
}

bool isEmpty(const Stack* const stack)
{
    return stack == NULL;
}
