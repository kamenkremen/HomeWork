#include <stdlib.h>

#include "Tests.h"
#include "CycleList.h"
#include "Solve.h"
#include "ErrorCodes.h"

static int CountingTest(void)
{
    int errorCode = 0;
    if (getSurvivedStartedPosition(10, 3, &errorCode) != 4 || errorCode != ok)
    {
        return 1;
    }
    if (getSurvivedStartedPosition(10, 10, &errorCode) != 8 || errorCode != ok)
    {
        return 2;
    }
    if (getSurvivedStartedPosition(20, 10, &errorCode) != 3 || errorCode != ok)
    {
        return 3;
    }
    if (getSurvivedStartedPosition(16, 1, &errorCode) != 16 || errorCode != ok)
    {
        return 4;
    }
    return ok;
}

static int finish(CycleList** const list, Position** const position, const int returnValue)
{
    deleteList(list);
    deletePosition(position);
    return returnValue;
}

static int listTest(void) {
    CycleList* list = createList();
    if (list == NULL)
    {
        return 1;
    }
    if (addElement(list, 10) != ok)
    {
        return finish(&list, NULL, 2);
    }
    int errorCode = ok;
    if (top(list, &errorCode) != 10 || errorCode != ok)
    {
        return finish(&list, NULL, 3);
    }
    if (addElement(list, 20) != ok)
    {
        return finish(&list, NULL, 4);
    }
    if (top(list, &errorCode) != 10 || errorCode != ok)
    {
        return finish(&list, NULL, 5);
    }
    Position* position = getStartPosition(list);
    if (position == NULL)
    {
        return finish(&list, NULL, 9);
    }
    if (deleteElement(list, position) != ok)
    {
        return finish(&list, &position, 6);
    }
    deletePosition(&position);
    if (getSize(list) != 1 || top(list, &errorCode) != 20 || errorCode != ok)
    {
        return finish(&list, NULL, 7);
    }
    position = getStartPosition(list);
    if (position == NULL)
    {
        return finish(&list, NULL, 10);
    }
    if (deleteElement(list, position))
    {
        return finish(&list, &position, 8);
    }
    return finish(&list, &position, ok);
}

bool tests(void)
{
    int result = CountingTest();
    bool isError = false;
    if (result != ok)
    {
        printf("ERROR IN SOLVING TEST, CASE %d\n", result);
        isError = false;
    }
    result = listTest();
    if (result != ok)
    {
        printf("ERROR IN LIST TEST, CASE %d\n", result);
        isError = true;
    }
    return isError;
}
