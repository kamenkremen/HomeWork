#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../Stack/Stack.h"

enum ERRORCODES 
{
	ok,
	memoryError,
	nullPointerError,
	division0Error,
};

int postfixCalculator(char* string, int* mainErrorCode)
{
	Stack* stack = NULL;
	for (size_t i = 0; i < strlen(string); ++i)
	{
		if (string[i] == ' ')
		{
			continue;
		}
		if (string[i] == '-' || string[i] == '/' || string[i] == '*' || string[i] == '+')
		{
			int errorCode = 0;
			int firstNumber = top(stack, &errorCode);
			if (pop(&stack))
			{
				freeStack(&stack);
				*mainErrorCode = nullPointerError;
				return nullPointerError;
			}
			if (errorCode)
			{
				freeStack(&stack);
				*mainErrorCode = errorCode;
				return errorCode;
			}
			int secondNumber = top(stack, &errorCode);
			if (errorCode)
			{
				freeStack(&stack);
				*mainErrorCode = errorCode;
				return errorCode;
			}
			if (pop(&stack))
			{
				freeStack(&stack);
				*mainErrorCode = nullPointerError;
				return nullPointerError;
			}
			if (string[i] == '-')
			{
				if (push(&stack, secondNumber - firstNumber))
				{
					freeStack(&stack);
					*mainErrorCode = memoryError;
					return memoryError;
				}
			}
			if (string[i] == '+')
			{
				if (push(&stack, secondNumber + firstNumber))
				{
					freeStack(&stack);
					*mainErrorCode = memoryError;
					return memoryError;
				}
			}
			if (string[i] == '*')
			{
				if (push(&stack, secondNumber * firstNumber))
				{
					int errorCode = 0;
					freeStack(&stack);
					*mainErrorCode = memoryError;
					return memoryError;
				}
			}
			if (string[i] == '/')
			{
				if (firstNumber == 0)
				{
					*mainErrorCode = division0Error;
					return division0Error;
				}
				if (push(&stack, secondNumber / firstNumber))
				{
					freeStack(&stack);
					*mainErrorCode = memoryError;
					return memoryError;
				}
			}
		}
		else
		{
			if (push(&stack, (int) string[i] - '0'))
			{
				freeStack(&stack);
				*mainErrorCode = memoryError;
				return memoryError;
			}
		}
	}
	int errorCode = 0;
	int result = top(stack, &errorCode);
	freeStack(&stack);
	if (errorCode)
	{
		*mainErrorCode = errorCode;
		return errorCode;
	}
	return result;
}

int testPostfixCalculator(void)
{
	char* test = "9 6 - 1 2 + *";
	int errorCode = 0;
	if (postfixCalculator(test, &errorCode) != 9)
	{
		return 1;
	}
	test = "9 0 /";
	if (postfixCalculator(test, &errorCode) != division0Error || errorCode != division0Error)
	{
		return 2;
	}
	test = "9 6 - 1 2 + * 9 * 9 * 9 * 9 *";
	if (postfixCalculator(test, &errorCode) != 59049)
	{
		return 3;
	}
	test = "1 9 - 9 - 9 - 9 -";
	if (postfixCalculator(test, &errorCode) != -35)
	{
		return 4;
	}
	return ok;
}

int testStack(void)
{
	Stack* stack = NULL;
	if (push(&stack, 10))
	{
		freeStack(&stack);
		return memoryError;
	}
	int errorCode = 0;
	if (top(stack, &errorCode) != 10)
	{
		return 4;
	}
	if (errorCode)
	{
		return errorCode;
	}
	if (pop(&stack))
	{
		return nullPointerError;
	}
	if (!isEmpty(stack))
	{
		return 5;
	}
	return ok;
}

int tests(void)
{
	int testPostfixCalculatorResult = testPostfixCalculator();
	if (testPostfixCalculatorResult)
	{
		return 10 + testPostfixCalculatorResult;
	}
	int testStackResult = testStack();
	if (testStackResult)
	{
		return 20 + testStackResult;
	}
	return ok;
}

int main(void)
{
	int errorCode = tests();
	if (errorCode)
	{
		printf("ERROR %d\n", errorCode);
		return errorCode;
	}
	int currentSize = 0;
	char symbol = 0;
	char* string = (char*)calloc(2, sizeof(char));
	int stringSize = 2;
	while ((symbol = getchar()) != '\n')
	{
		if (strlen(string) + 3 >= stringSize)
		{
			stringSize *= 2;
			string = realloc(string, sizeof(char) * stringSize);
			if (string == NULL)
			{
				return 1;
			}
		}
		if (strncat(string, &symbol, 1) == NULL)
		{
			printf("MEMORY ERROR");
			return memoryError;
		}
	}
	errorCode = 0;
	int result = postfixCalculator(string, &errorCode);
	if (errorCode)
	{
		printf("ERROR IN CALCULATION %d", errorCode);
		return errorCode;
	}
	printf("Result = %d", result);
	return 0;
}