#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "Stack.h"

enum ERRORCODES
{
	ok,
	memoryError,
	nullPointerError,
};

enum BALANCE_RETURNS
{
	notBalanced = -1,
	balanced = 0,
};

const char* TEST_ERRORS[5] = { "ok", "IS CLOSING FUNCTION", "STACK", "SAME TYPE FUNCTION", "CHECK BALANCE FUNCTION"};

bool isClosing(const char bracket)
{
	return (bracket == ')' || bracket == '}' || bracket == ']');
}

int finish(Stack** stack, const int returnValue)
{
	if (*stack != NULL)
	{
		freeStack(stack);
	}
	return returnValue;
}

bool sameType(const char firstBracket, const char secondBracket)
{
	if (firstBracket == '(')
	{
		return secondBracket == ')';
	}
	if (firstBracket == '{')
	{
		return secondBracket == '}';
	}
	if (firstBracket == '[')
	{
		return secondBracket == ']';
	}
	return false;
}

int checkBalance(const char* const string)
{
	Stack* stack = NULL;
	for (size_t i = 0; i < strlen(string); ++i)
	{
		if (isClosing(string[i]))
		{
			int errorCode = 0;
			if (isEmpty(stack))
			{
				return finish(&stack, notBalanced);
			}
			const char bracket = top(stack, &errorCode);
			if (errorCode != ok)
			{
				return finish(&stack, errorCode);
			}
			if (!isClosing(bracket) && sameType(bracket, string[i]))
			{
				if (pop(&stack) != ok)
				{
					return finish(&stack, nullPointerError);
				}
				continue;
			}
			return finish(&stack, notBalanced);
		}
		if (push(&stack, string[i]) != ok)
		{
			finish(&stack, memoryError);
		}
	}
	if (isEmpty(stack))
	{
		return balanced;
	}
	return finish(&stack, notBalanced);
}

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

int testIsClosing(void)
{
	if (isClosing('('))
	{
		return 1;
	}
	if (!isClosing(')'))
	{
		return 2;
	}
	if (!isClosing('}'))
	{
		return 3;
	}
	return ok;
}

int testSameType(void)
{
	if (!sameType('(', ')'))
	{
		return 1;
	}
	if (sameType('(', '}'))
	{
		return 2;
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
	const int testIsClosingResult = testIsClosing();
	if (testIsClosingResult != ok)
	{
		return 10 + testIsClosingResult;
	}
	const int testStackResult = testStack();
	if (testStackResult != ok)
	{
		return 20 + testStackResult;
	}
	const int testSameTypeResult = testSameType();
	if (testSameTypeResult != ok)
	{
		return 30 + testSameTypeResult;
	}
	const int testCheckBalanceResult = testCheckBalance();
	if (testCheckBalanceResult != ok)
	{
		return 40 + testCheckBalanceResult;
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