#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "PostfixCalculator.h"
#include "Stack.h"



const char* TEST_ERRORS[4] = { "ok", "POSTFIX CALCULATOR FUNCTION", "STACK" };

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

int tests(void)
{
	const int testPostfixCalculatorResult = testPostfixCalculator();
	if (testPostfixCalculatorResult != ok)
	{
		return 10 + testPostfixCalculatorResult;
	}
	const int testStackResult = testStack();
	if (testStackResult != ok)
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
		printf("ERROR IN %s, TEST CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
		return errorCode;
	}
	size_t currentSize = 0;
	char symbol = 0;
	char* string = (char*)calloc(2, sizeof(char));
	size_t stringSize = 2;
	printf("Enter the string to calculate:\n");
	size_t amountOfNumbers = 0;
	while ((symbol = getchar()) != '\n')
	{
		if (symbol == ' ')
		{
			continue;
		}
		if (symbol - '0' < 0 || symbol - '0' > 9)
		{
			if (symbol != '/' && symbol != '*' && symbol != '+' && symbol != '-' || amountOfNumbers < 2)
			{
				printf("Incorrect input\n");
				free(string);
				return inputError;
			}
			--amountOfNumbers;
		}
		else
		{
			++amountOfNumbers;
		}
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
	errorCode = 0;
	int result = postfixCalculator(string, &errorCode);
	if (errorCode)
	{
		printf("ERROR IN CALCULATION %d\n", errorCode);
		free(string);
		return errorCode;
	}
	printf("Result = %d\n", result);
	free(string);
	return ok;
}
