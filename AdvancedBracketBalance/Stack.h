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
typedef char StackValue;
//объявление самого стэка
typedef struct Stack Stack;
//добавление в стэк элемента
int push(Stack** stack, const StackValue value);
//удаление верхнего элемента из стэка
int pop(Stack** stack);
//просмотр верхнего элемента стэка
StackValue top(Stack* stack, int* errorCode);
//освобождение стэка
void freeStack(Stack** stack);
//проверка, пустой ли стэк
bool isEmpty(Stack* stack);
