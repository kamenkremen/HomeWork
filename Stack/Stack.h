#pragma once
//���� ������ ��� �����
enum ERRORCODES_STACK
{
	stackOk,
	stackMemoryError,
	stackNullPointerError,
};
//���������� ������ �����
typedef struct Stack Stack;
//���������� � ���� ��������
int push(Stack** stack, const char value);
//�������� �������� �������� �� �����
int pop(Stack** stack);
//�������� �������� �������� �����
char top(Stack* stack, int* errorCode);
//������������ �����
int freeStack(Stack** stack);
//��������, ������ �� ����
int isEmpty(Stack* stack);