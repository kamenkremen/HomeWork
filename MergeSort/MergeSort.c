#include "MergeSort.h"
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "ListOfLists.h"
#include <string.h>
#include "ErrorCodes.h"

List* merge(const List* const first, const List* const second, const bool sortByName, int* errorCode)
{
	List* newList = createList();
	if (newList == NULL)
	{
		*errorCode = memoryError;
		deleteList(&newList);
		return;
	}
	size_t i = 0;
	size_t j = 0;
	while (i < getSize(first) || j < getSize(second))
	{
		if (i >= getSize(first))
		{
			int errorCode2 = 0;
			ListValue value = getElement(second, j, &errorCode2);
			if (errorCode2 != ok)
			{
				*errorCode = errorCode2;
				deleteList(&newList);
				return;
			}
			if (addElement(newList, value) != ok)
			{
				*errorCode = memoryError;
				deleteList(&newList);
				return;
			}
			++j;
			continue;
		}
		if (j >= getSize(second))
		{
			int errorCode2 = 0;
			ListValue value = getElement(first, i, &errorCode2);
			if (errorCode2 != ok)
			{
				*errorCode = errorCode2;
				deleteList(&newList);
				return;
			}
			if (addElement(newList, value) != ok)
			{
				*errorCode = memoryError;
				deleteList(&newList);
				return;
			}
			++i;
			continue;
		}
		int errorCode2 = 0;
		ListValue firstValue = getElement(first, i, &errorCode2);
		if (errorCode2 != ok)
		{
			*errorCode = errorCode2;
			deleteList(&newList);
			return;
		}
		ListValue secondValue = getElement(second, j, &errorCode2);
		if (errorCode2 != ok)
		{
			*errorCode = errorCode2;
			deleteList(&newList);
			return;
		}
		char* firstValueToSort = 0;
		char* secondValueToSort = 0;
		if (sortByName)
		{
			firstValueToSort = firstValue.name;
			secondValueToSort = secondValue.name;
		}
		else
		{
			firstValueToSort = firstValue.number;
			secondValueToSort = secondValue.number;
		}
		if (strcmp(firstValueToSort, secondValueToSort) > 0)
		{
			if (addElement(newList, secondValue) != ok)
			{
				*errorCode = memoryError;
				deleteList(&newList);
				return;
			}
			++j;
		}
		else
		{
			if (addElement(newList, firstValue) != ok)
			{
				*errorCode = memoryError;
				deleteList(&newList);
				return;
			}
			++i;
		}
	}
	return newList;
}

void sort(ListOfLists* const list, const bool sortByName, int* mainErrorCode)
{
	int errorCode = 0;
	while (getSizeOfListOfLists(list) > 1)
	{
		List* firstList = getList(list, 0, &errorCode);
		//printf("%d\n", getSize(list));
		if (errorCode != ok)
		{
			*mainErrorCode = errorCode;
			return;
		}
		List* secondList = getList(list, 1, &errorCode);
		if (errorCode != ok)
		{
			*mainErrorCode = errorCode;
			return;
		}
		deleteListFromListOfLists(list, 0);
		deleteListFromListOfLists(list, 0);
		List* newList = merge(firstList, secondList, sortByName, &errorCode);
		if (errorCode != ok)
		{
			deleteList(&newList);
			*mainErrorCode = errorCode;
			return;
		}
		if (addList(list, newList) != ok)
		{
			deleteList(&newList);
			*mainErrorCode = memoryError;
			return;
		}
	}
}



void mergeSort(List** const list, const bool sortByName, int* mainErrorCode)
{
	ListOfLists* listOfLists = createListOfLists();
	if (listOfLists == NULL)
	{
		return memoryError;
	}
	int errorCode = 0;
	for (size_t i = 0; i < getSize(*list); ++i)
	{
		List* listElement = createList();
		if (listElement == NULL)
		{
			return memoryError;
		}
		ListValue value = getElement(*list, i, &errorCode);
		if (errorCode != ok)
		{
			return errorCode;
		}
		addElement(listElement, value);
		addList(listOfLists, listElement);
	}

	sort(listOfLists, sortByName, &errorCode);
	if (errorCode != ok)
	{
		*mainErrorCode = errorCode;
		return;
	}
	*list = getList(listOfLists, 0, &errorCode);
	if (errorCode != ok)
	{
		*list = NULL;
		*mainErrorCode = errorCode;
		return;
	}
}