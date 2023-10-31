#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "Stack.h"
#include "BracketBalance.h"

const char* TEST_ERRORS[5] = { "ok", "STACK", "CHECK BALANCE FUNCTION"};

int testStack(void)
{
	Stack* stack = NULL;
	if (push(&stack, 10) != ok)
	{
		freeStack(&stack);
		return memoryError;
	}
	int errorCode = 0;
	if (top(stack, &errorCode) != 10)
	{
		freeStack(&stack);
		return 4;
	}
	if (errorCode)
	{
		freeStack(&stack);
		return errorCode;
	}
	if (pop(&stack) != ok)
	{
		return nullPointerError;
	}
	if (!isEmpty(stack))
	{
		freeStack(&stack);
		return 5;
	}
	return ok;
}

int testCheckBalance(void)
{
	if (checkBalance("())") != notBalanced)
	{
		return 1;
	}
	if (checkBalance("({})") != balanced)
	{
		return 2;
	}
	if (checkBalance("") != balanced)
	{
		return 3;
	}
	if (checkBalance("({[)}]") != notBalanced)
	{
		return 4;
	}
	return ok;
}

int tests(void)
{
	const int testStackResult = testStack();
	if (testStackResult != ok)
	{
		return 10 + testStackResult;
	}
	const int testCheckBalanceResult = testCheckBalance();
	if (testCheckBalanceResult != ok)
	{
		return 20 + testCheckBalanceResult;
	}
	return ok;
}

int main(void)
{
	int errorCode = tests();
	if (errorCode)
	{
		printf("ERROR IN %s, TEST CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
		return errorCode;
	}
	size_t currentSize = 0;
	char symbol = 0;
	char* string = (char*)calloc(2, sizeof(char));
	size_t stringSize = 2;
	printf("Enter the brackets:\n");
	while ((symbol = getchar()) != '\n')
	{
		if (strlen(string) + 3 >= stringSize)
		{
			stringSize *= 2;
			char* buffer = (char*)realloc(string, sizeof(char) * stringSize);
			if (buffer == NULL)
			{
				free(string);
				return memoryError;
			}
			string = buffer;
		}
		if (strncat(string, &symbol, 1) == NULL)
		{
			printf("MEMORY ERROR\n");
			free(string);
			return memoryError;
		}
	}
	const int result = checkBalance(string);
	if (result > balanced)
	{
		printf("ERROR %d\n", result);
		free(string);
		return result;
	}
	printf("%s", result == balanced ? "Balanced\n" : "Not balanced\n");
	free(string);
	return ok;
}