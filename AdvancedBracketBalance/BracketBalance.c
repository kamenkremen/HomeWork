#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "BracketBalance.h"
#include <stdbool.h>

static bool isClosing(const char bracket)
{
	return (bracket == ')' || bracket == '}' || bracket == ']');
}

static int finish(Stack** stack, const int returnValue)
{
	if (*stack != NULL)
	{
		freeStack(stack);
	}
	return returnValue;
}

static bool sameType(const char firstBracket, const char secondBracket)
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
		if (string[i] != '[' && string[i] != ']' && string[i] != '{' && string[i] != '}' && string[i] != '(' && string[i] != ')')
		{
			continue;
		}
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