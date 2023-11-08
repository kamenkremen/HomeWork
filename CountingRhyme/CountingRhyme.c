#include "CycleList.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


enum ERRORCODES
{
	ok,
	memoryError,
	noSuchElement,
	nullPointerError,
	inputError,
};

static char* ERROR_NAMES[5] = {
	"OK",
	"MEMORY ERROR",
	"NO SUCH ELEMENT",
	"NULL POINTER ERROR",
	"INPUT ERROR",
};

static char* TEST_ERRORS[3] = {
	"OK",
	"COUNTING",
	"LIST"
};

int getSurvivedStartedPosition(const size_t n, const size_t m, int* errorCode)
{
	CycleList* list = createList();
	if (list == NULL)
	{
		*errorCode = memoryError;
		return memoryError;
	}
	for (size_t i = 0; i < n; ++i)
	{
		if (addElement(list, i) != ok)
		{
			*errorCode = memoryError;
			return memoryError;
		}
	}
	size_t current = m;
	while (getSize(list) > 1)
	{
		if (deleteElement(list, current) != ok)
		{
			*errorCode = nullPointerError;
			return nullPointerError;
		}
		current += m;
		--current;
	}
	if (isEmpty(list))
	{
		return nullPointerError;
	}
	const int result = top(list) + 1;
	deleteList(&list);
	return result;
}

int CountingTest(void)
{
	int errorCode = 0;
	if (getSurvivedStartedPosition(10, 3, &errorCode) != 10 || errorCode != ok) 
	{
		return 1;
	}
	if (getSurvivedStartedPosition(10, 10, &errorCode) != 4 || errorCode != ok)
	{
		return 2;
	}
	if (getSurvivedStartedPosition(20, 10, &errorCode) != 7 || errorCode != ok)
	{
		return 3;
	}
	if (getSurvivedStartedPosition(16, 1, &errorCode) != 16 || errorCode != ok)
	{
		return 4;
	}
	return ok;
}

int listTest(void) {
	CycleList* list = createList();
	if (list == NULL)
	{
		return 1;
	}
	if (addElement(list, 10) != ok)
	{
		deleteList(&list);
		return 2;
	}
	if (get(list, 0) != 10)
	{
		deleteList(&list);
		return 3;
	}
	if (addElement(list, 20) != ok)
	{
		deleteList(&list);
		return 4;
	}
	if (get(list, 1) != 20 || get(list, 0) != 10)
	{
		deleteList(&list);
		return 5;
	}
	if (deleteElement(list, 0) != ok)
	{
		deleteList(&list);
		return 6;
	}
	if (getSize(list) != 1 || get(list, 0) != 20)
	{
		deleteList(&list);
		return 7;
	}
	if (deleteElement(list, 0) != ok)
	{
		deleteList(&list);
		return 8;
	}
	deleteList(&list);
	return ok;
}

int tests(void)
{
	int result = CountingTest();
	if (result != ok)
	{
		return 10 + result;
	}
	result = listTest();
	if (result != ok)
	{
		return 20 + result;
	}
	return ok;
}

int main(void)
{
	int errorCode = tests();
	if (errorCode != ok)
	{
		printf("ERROR IN %s TEST, CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
		return errorCode;
	}
	size_t n = 0;
	size_t m = 0;
	printf("Enter the amount of warriors(n):\n");
	if (scanf_s("%lu", &n) != 1)
	{
		printf("INPUT ERROR\n");
		return inputError;
	}
	printf("Enter the step in which warriors will be killed(m):\n");
	if (scanf_s("%lu", &m) != 1)
	{
		printf("INPUT ERROR\n");
		return inputError;
	}
	errorCode = ok;
	const int result = getSurvivedStartedPosition(n, m, &errorCode);
	if (errorCode != ok)
	{
		printf("ERROR %s\n", ERROR_NAMES[errorCode]);
		return errorCode;
	}
	printf("To not get killed, you should be on the %d position from the start\n", result);
	return ok;
}