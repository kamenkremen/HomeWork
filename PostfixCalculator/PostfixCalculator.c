#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Stack.h"

enum ERRORCODES 
{
	ok,
	memoryError,
	nullPointerError,
	division0Error,
};

const char* TEST_ERRORS[4] = { "ok", "POSTFIX CALCULATOR FUNCTION", "STACK", "PROCESSING OPERATION" };

int processTheOperation(const char operation, const int firstNumber, const int secondNumber, int* const errorCode)
{
	if (operation == '-')
	{
		return firstNumber - secondNumber;
	}
	if (operation == '+')
	{
		return firstNumber + secondNumber;
	}
	if (operation == '*')
	{
		return firstNumber * secondNumber;
	}
	if (secondNumber == 0)
	{
		*errorCode = division0Error;
		return division0Error;
	}
	return firstNumber / secondNumber;
}

int finish(Stack** stack, int *mainErrorCode, const int errorCode)
{
	
	if (*stack != NULL)
	{
		freeStack(stack);
	}
	*mainErrorCode = errorCode;
	return errorCode;

}

int postfixCalculator(const char* const string, int* mainErrorCode)
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
			int errorCode = ok;
			const int secondNumber = top(stack, &errorCode);
			if (errorCode != ok)
			{
				return finish(&stack, mainErrorCode, errorCode);
			}
			if (pop(&stack) != ok)
			{
				return finish(&stack, mainErrorCode, nullPointerError);
			}
			const int firstNumber = top(stack, &errorCode);
			if (errorCode != ok)
			{
				return finish(&stack, mainErrorCode, errorCode);
			}
			if (pop(&stack) != ok)
			{
				return finish(&stack, mainErrorCode, nullPointerError);
			}
			const int thirdNumber = processTheOperation(string[i], firstNumber, secondNumber, &errorCode);
			if (errorCode != ok)
			{
				return finish(&stack, mainErrorCode, errorCode);
			}
			if (push(&stack, thirdNumber) != ok)
			{
				return finish(&stack, mainErrorCode, memoryError);
			}
		}
		else
		{
			if (push(&stack, (int) string[i] - '0') != ok)
			{
				return finish(&stack, mainErrorCode, memoryError);
			}
		}
	}
	int errorCode = ok;
	const int result = top(stack, &errorCode);
	if (errorCode)
	{
		return finish(&stack, mainErrorCode, errorCode);
	}
	freeStack(&stack);
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

int testProcessOperation(void)
{
	int errorCode = ok;
	if (processTheOperation('-', 5, 3, &errorCode) != 2 || errorCode != ok)
	{
		return 1;
	}
	if (processTheOperation('/', 5, 0, &errorCode) != division0Error || errorCode != division0Error)
	{
		return 2;
	}
	errorCode = ok;
	if (processTheOperation('-', 100, -100, &errorCode) != 200 || errorCode != ok)
	{
		return 3;
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
	const int testProcessOperationResult = testProcessOperation();
	if (testProcessOperationResult != ok)
	{
		return 30 + testProcessOperationResult;
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
