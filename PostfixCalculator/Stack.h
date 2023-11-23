#pragma once
#include <stdbool.h>
//коды ошибок для стэка
enum ERRORCODES_STACK
{
    stackOk,
    stackMemoryError,
    stackNullPointerError,
};
//объявление значения стэка
typedef int StackValue;
//объявление самого стэка
typedef struct Stack Stack;
//добавление в стэк элемента
int push(Stack** const stack, const StackValue value);
//удаление верхнего элемента из стэка
int pop(Stack** const stack);
//просмотр верхнего элемента стэка
StackValue top(const Stack* const stack, int* errorCode);
//освобождение стэка
void freeStack(Stack** const stack);
//проверка, пустой ли стэк
bool isEmpty(const Stack* const stack);
