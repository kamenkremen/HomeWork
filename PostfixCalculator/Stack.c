#include <stdlib.h>
#include "Stack.h"

struct Stack
{
    StackValue value;
    struct Stack* previous;
};

int push(Stack** const head, const StackValue value)
{
    Stack* next = (Stack*)malloc(sizeof(Stack));
    if (next == NULL)
    {
        return stackMemoryError;
    }
    next->value = value;
    next->previous = *head;
    *head = next;
    return stackOk;
}

int pop(Stack** const head)
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

StackValue top(const Stack* const head, int* const errorCode)
{
    if (isEmpty(head))
    {
        *errorCode = stackNullPointerError;
        return 0;
    }
    return head->value;
}

void freeStack(Stack** const head)
{
    while (!isEmpty(*head))
    {
        pop(head);
    }
}

bool isEmpty(const Stack* const stack)
{
    return stack == NULL;
}
