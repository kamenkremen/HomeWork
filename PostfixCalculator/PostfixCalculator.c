#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "PostfixCalculator.h"


static int processTheOperation(const char operation, const int firstNumber, const int secondNumber, int* const errorCode)
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

static int finish(Stack** stack, int* mainErrorCode, const int errorCode)
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
			if (string[i] - '0' < 0 || string[i] - '0' > 9)
			{
				return finish(&stack, mainErrorCode, inputError);
			}
			if (push(&stack, (int)string[i] - '0') != ok)
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
