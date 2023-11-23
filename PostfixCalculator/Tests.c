#include <stdio.h>
#include <stdlib.h>

#include "Tests.h"
#include "Stack.h"
#include "PostfixCalculator.h"
#include "ErrorCodes.h"

const char* TEST_ERRORS[4] = { "ok", "POSTFIX CALCULATOR FUNCTION", "STACK" };

static int testPostfixCalculator(void)
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

static int testStack(void)
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

static finish(const int errorCode)
{
	printf("ERROR IN %s TEST, CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
	return errorCode;
}

int tests(void)
{
	int errorCode = testPostfixCalculator();;
	if (errorCode != ok)
	{
		return finish(errorCode);
	}
	errorCode = testStack();
	if (errorCode != ok)
	{
		return finish(errorCode);
	}
	return ok;
}