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
int push(Stack** stack, const StackValue value);
//�������� �������� �������� �� �����
int pop(Stack** stack);
//�������� �������� �������� �����
StackValue top(Stack* stack, int* errorCode);
//������������ �����
int freeStack(Stack** stack);
//��������, ������ �� ����
int isEmpty(Stack* stack);