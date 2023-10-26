#pragma once
//коды ошибок для стэка
enum ERRORCODES_STACK
{
	stackOk,
	stackMemoryError,
	stackNullPointerError,
};
//объявление самого стэка
typedef struct Stack Stack;
//добавление в стэк элемента
int push(Stack** stack, const char value);
//удаление верхнего элемента из стэка
int pop(Stack** stack);
//просмотр верхнего элемента стэка
char top(Stack* stack, int* errorCode);
//освобождение стэка
int freeStack(Stack** stack);
//проверка, пустой ли стэк
int isEmpty(Stack* stack);