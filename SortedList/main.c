#include <stdio.h>
#include <stdlib.h>
#include "SortedList.h"
#include "Test.h"

int finish(SortedList** list, const int errorCode)
{
	deleteList(list);
	return errorCode;
}

enum OPERATIONS
{
	exit,
	add,
	remove,
	print,
};

int main(void)
{
	const int errorCode = test();
	if (errorCode != ok)
	{
		printf("ERROR IN SORTED LIST TEST, CASE %d\n", errorCode);
		return errorCode;
	}
	SortedList* list = createList();
	if (list == NULL)
	{
		printf("MEMORY ERROR\n");
		return memoryError;
	}
	while (true)
	{
		printf("Enter number of the operation:\n0 - exit\n1 - add element to the\
		list\n2 - delete element from the list\n3 - print list\n");
		const int operation = 0;
		if (scanf_s("%d", &operation) != 1)
		{
			printf("INPUT ERROR\n");
			return finish(&list, inputError);
		}
		switch (operation)
		{
			case exit:
				deleteList(&list);
				break;
			case add:
				printf("Enter value to add:\n");
				const int value = 0;
				if (scanf_s("%d", &value) != 1)
				{
					printf("INPUT ERROR\n");
					return finish(&list, inputError);
				}
				int errorCode = addElement(&list, value);
				if (errorCode != ok)
				{
					printf("MEMORY ERROR\n");
					return finish(&list, memoryError);
				}
				break;
			case remove:
				printf("Enter value to remove:\n");
				const int value = 0;
				if (scanf_s("%d", &value) != 1)
				{
					printf("INPUT ERROR\n");
					return finish(&list, inputError);
				}
				int errorCode = deleteElement(&list, value);
				if (errorCode != ok)
				{
					if (errorCode == listNoSuchElement)
					{
						printf("No element has been removed\n");
						continue;
					}
					printf("ERROR %d\n", errorCode);
					return finish(&list, errorCode);
				}
				break;
			case print:
				printList(list);
		}
	}
	return ok;
}
