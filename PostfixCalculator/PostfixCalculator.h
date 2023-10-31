#pragma once
enum ERRORCODES
{
	ok,
	memoryError,
	nullPointerError,
	division0Error,
	inputError,
};
// сама функция постфиксного калькулятора
int postfixCalculator(const char* const string, int* errorCode);