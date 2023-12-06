#include <stdlib.h>
#include <stdio.h>

#include "SortedList.h"
#include "Test.h"

static int finish(SortedList** list, const int returnValue)
{
    deleteList(list);
    return returnValue;
}

int test(void)
{
    int errorCode = ok;
    SortedList* list = createList();
    if (list == NULL)
    {
        return memoryError;
    }
    if (!deleteElement(list, 128745))
    {
        return finish(&list, 10);
    }
    if (addElement(list, 10) != ok)
    {
        return finish(&list, 1);
    }
    if (deleteElement(list, 10))
    {
        return finish(&list, 2);
    }
    if (!isEmpty(list))
    {
        return finish(&list, 3);
    }
    if (addElement(list, 10) != ok)
    {
        return finish(&list, 4);
    }
    if (addElement(list, 6) != ok)
    {
        return finish(&list, 5);
    }
    if (addElement(list, 8) != ok)
    {
        return finish(&list, 6);
    }
    if (top(list, &errorCode) != 6 || errorCode != ok)
    {
        return finish(&list, 7);
    }
    if (deleteElement(list, 6))
    {
        return finish(&list, 8);
    }
    if (top(list, &errorCode) != 8 || errorCode != ok)
    {
        return finish(&list, 9);
    }
    return finish(&list, ok);
}
