#pragma once
#include <stdbool.h>
//���� ������ ��� �����
enum ERRORCODES_STACK
{
    stackOk,
    stackMemoryError,
    stackNullPointerError,
};
//���������� �������� �����
typedef int StackValue;
//���������� ������ �����
typedef struct Stack Stack;
//���������� � ���� ��������
int push(Stack** const stack, const StackValue value);
//�������� �������� �������� �� �����
int pop(Stack** const stack);
//�������� �������� �������� �����
StackValue top(const Stack* const stack, int* errorCode);
//������������ �����
void freeStack(Stack** const stack);
//��������, ������ �� ����
bool isEmpty(const Stack* const stack);
