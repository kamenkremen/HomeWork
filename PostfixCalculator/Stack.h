#pragma once
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
int push(Stack** stack, const int value);
//удаление верхнего элемента из стэка
int pop(Stack** stack);
//просмотр верхнего элемента стэка
int top(Stack* stack, int* errorCode);
//освобождение стэка
int freeStack(Stack** stack);
//проверка, пустой ли стэк
int isEmpty(Stack* stack);