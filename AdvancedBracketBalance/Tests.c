#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "BracketBalance.h"
#include "ErrorCodes.h"

const char* TEST_ERRORS[5] = { "ok", "STACK", "CHECK BALANCE FUNCTION" };

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

static int testCheckBalance(void)
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
        printf("ERROR IN STACK TEST, CASE %d\n", testStackResult);
        return 10 + testStackResult;
    }
    const int testCheckBalanceResult = testCheckBalance();
    if (testCheckBalanceResult != ok)
    {
        printf("ERROR IN CHECK BRACKET BALANCE TEST, CASE %d\n", testCheckBalanceResult);
        return 20 + testCheckBalanceResult;
    }
    return ok;
}
