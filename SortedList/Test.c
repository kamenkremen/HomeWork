#include <stdlib.h>
#include <stdio.h>

#include "SortedList.h"
#include "Test.h"

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
		return 10;
	}
	if (addElement(list, 10) != ok)
	{
		deleteList(&list);
		return 1;
	}
	if (deleteElement(list, 10) != ok)
	{
		deleteList(&list);
		return 2;
	}
	if (!isEmpty(list))
	{
		deleteList(&list);
		return 3;
	}
	if (addElement(list, 10) != ok)
	{
		deleteList(&list);
		return 4;
	}
	if (addElement(list, 6) != ok)
	{
		deleteList(&list);
		return 5;
	}
	if (addElement(list, 8) != ok)
	{
		deleteList(&list);
		return 6;
	}
	if (top(list, &errorCode) != 6 || errorCode != ok)
	{
		deleteList(&list);
		return 7;
	}
	if (deleteElement(list, 6) != ok)
	{
		deleteList(&list);
		return 8;
	}

	if (top(list, &errorCode) != 8 || errorCode != ok)
	{
		deleteList(&list);
		return 9;
	}
	deleteList(&list);
	return ok;
}