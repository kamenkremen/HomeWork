#pragma once
enum ERRORCODES
{
	ok,
	memoryError,
	nullPointerError,
	division0Error,
	inputError,
};
// ���� ������� ������������ ������������
int postfixCalculator(const char* const string, int* errorCode);