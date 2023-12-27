#pragma once

#include <stdbool.h>

//���������� �������� �����
typedef char StackValue;

//���������� ������ �����
typedef struct Stack Stack;

//���������� � ���� ��������
int push(Stack** const stack, const StackValue value);

//�������� �������� �������� �� �����
int pop(Stack** const stack);

//�������� �������� �������� �����
StackValue top(const Stack* const stack, int* const errorCode);

//������������ �����
void freeStack(Stack** const stack);

//��������, ������ �� ����
bool isEmpty(const Stack* const stack);
