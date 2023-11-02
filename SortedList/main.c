#include <stdio.h>
#include <stdlib.h>
#include "SortedList.h"

enum ERRORCODES
{
	ok,
	memoryError,
	inputError,
};

int testList(void)
{
	SortedList* list = createList();
	if (list == NULL)
	{
		return memoryError;
	}
	if (addElement(list, 10) != ok)
	{
		return 1;
	}
	if (deleteElement(list, 10) != ok)
	{
		return 2;
	}
	if (!isEmpty(list))
	{
		return 3;
	}
	if (addElement(list, 10) != ok)
	{
		return 4;
	}
	if (addElement(list, 6) != ok)
	{
		return 5;
	}
	if (addElement(list, 8) != ok)
	{
		return 6;
	}
	if (top(list) != 6)
	{
		return 7;
	}
	if (deleteElement(list, 6) != ok)
	{
		return 8;
	}
	if (top(list) != 8)
	{
		return 9;
	}
	deleteList(&list);
	return ok;
}

int tests(void)
{
	return testList();
	
}

int main(void)
{
	SortedList* list = createList();
	const int errorCode = tests();
	if (errorCode != ok)
	{
		printf("ERROR IN SORTED LIST TEST, CASE %d\n", errorCode);
		return errorCode;
	}
	if (list == NULL)
	{
		printf("MEMORY ERROR\n");
		return memoryError;
	}
	while (1)
	{
		printf("Enter number of the operation:\n0 - exit\n1 - add element to the list\n2 - delete element from the list\n3 - print list\n");
		const int operation = 0;
		if (scanf_s("%d", &operation) != 1)
		{
			printf("INPUT ERROR\n");
			deleteList(&list);
			return inputError;
		}
		if (operation == 0)
		{
			deleteList(&list);
			break;
		}
		if (operation == 1)
		{
			printf("Enter value to add:\n");
			const int value = 0;
			if (scanf_s("%d", &value) != 1)
			{
				printf("INPUT ERROR\n");
				deleteList(&list);
				return inputError;
			}
			int errorCode = addElement(&list, value);
			if (errorCode != ok)
			{
				printf("MEMORY ERROR\n");
				deleteList(&list);
				return memoryError;
			}
			continue;
		}
		if (operation == 2)
		{
			printf("Enter value to remove:\n");
			const int value = 0;
			if (scanf_s("%d", &value) != 1)
			{
				printf("INPUT ERROR\n");
				deleteList(&list);
				return inputError;
			}
			int errorCode = deleteElement(&list, value);
			if (errorCode != ok)
			{
				if (errorCode == listNoSuchElement)
				{
					printf("No element has been removed\n");
					continue;
				}
				printf("ERROR %s\n", errorCode);
				deleteList(&list);
				return errorCode;
			}
			continue;
		}
		if (operation == 3)
		{
			printList(list);
		}
	}
	return ok;
}