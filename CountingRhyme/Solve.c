#include <stdlib.h>

#include "Solve.h"
#include "CycleList.h"
#include "ErrorCodes.h"

static int finish(CycleList** const list, Position** const position, int* const errorCode, const int error)
{
    deleteList(list);
    deletePosition(position);
    *errorCode = error;
    return 1;
}

int getSurvivedStartedPosition(const size_t n, const size_t m, int* const errorCode)
{
    CycleList* list = createList();
    if (list == NULL)
    {
        return finish(NULL, NULL, errorCode, memoryError);
    }
    for (size_t i = 0; i < n; ++i)
    {
        if (addElement(list, i) != ok)
        {
            return finish(&list, NULL, errorCode, memoryError);
        }
    }
    while (getSize(list) > 1)
    {
        Position* position = getStartPosition(list);
        if (position == NULL)
        {
            return finish(&list, NULL, errorCode, memoryError);
        }
        for (size_t i = 1; i < m; ++i)
        {
            if (movePostionForward(position))
            {
                return finish(&list, &position, errorCode, nullPointerError);
            }
        }
        if (deleteElement(list, position))
        {
            return finish(&list, &position, errorCode, nullPointerError);
        }
        deletePosition(&position);
    }
    if (getSize(list) == 0)
    {
        return finish(&list, NULL, errorCode, solvingError);
    }
    const int result = top(list, &errorCode) + 1;
    deleteList(&list);
    return result;
}
