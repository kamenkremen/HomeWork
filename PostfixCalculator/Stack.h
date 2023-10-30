#pragma once
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
int push(Stack** stack, const int value);
//�������� �������� �������� �� �����
int pop(Stack** stack);
//�������� �������� �������� �����
int top(Stack* stack, int* errorCode);
//������������ �����
int freeStack(Stack** stack);
//��������, ������ �� ����
int isEmpty(Stack* stack);