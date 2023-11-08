#include "MergeSort.h"
#include "ErrorCodes.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* ERROR_NAMES[6] =
{
	"OK",
	"MEMORY ERROR",
	"NULL POINTER ERROR",
	"NO SUCH ELEMENT ERROR",
	"FILE ERROR",
	"INPUT ERROR",
};

char* TEST_ERRORS[3] =
{
	"OK",
	"MERGE SORT",
	"READ FILE",
};

int readFile(List* const list, const FILE* const file)
{
	size_t currentSize = 0;
	char symbol = 0;
	char* string = (char*)calloc(2, sizeof(char));
	if (string == NULL)
	{
		return memoryError;
	}
	size_t stringSize = 2;
	ListValue* value = calloc(1, sizeof(ListValue));
	if (value == NULL)
	{
		free(string);
		return memoryError;
	}
	while ((symbol = getc(file)))
	{
		if (symbol == '-')
		{
			string[currentSize] = '\0';
			value->name = string;
			string = (char*)calloc(2, sizeof(char));
			currentSize = 0;
			stringSize = 2;
			if (string == NULL)
			{
				free(value);
				return memoryError;
			}
			continue;
		}
		if (symbol == '\n' || symbol == EOF)
		{
			string[currentSize] = '\0';
			value->number = string;
			if (addElement(list, *value) != ok)
			{
				free(string);
				free(value);
				return memoryError;
			}
			value = calloc(1, sizeof(ListValue));
			if (value == NULL)
			{
				free(string);
				return memoryError;
			}
			string = (char*)calloc(2, sizeof(char));
			currentSize = 0;
			stringSize = 2;
			if (string == NULL)
			{
				free(value);
				return memoryError;
			}
			if (symbol == EOF)
			{
				free(string);
				free(value);
				return ok;
			}
			continue;
		}
		if (currentSize + 3 >= stringSize)
		{
			stringSize *= 2;
			char* buffer = (char*)realloc(string, sizeof(char) * stringSize);
			if (buffer == NULL)
			{
				free(string);
				free(value);
				return memoryError;
			}
			string = buffer;
		}
		string[currentSize] = symbol;
		++currentSize;
	}
	free(string);
	free(value);
	return ok;
}

int readFileTest(void)
{
	FILE* file = fopen("test.txt", "r");
	if (file == NULL)
	{
		return 1;
	}
	List* list = createList();
	if (list == NULL)
	{
		fclose(file);
		return 1;
	}
	readFile(list, file);
	int errorCode = 0;
	ListValue value1;
	value1.name = "test1";
	value1.number = "1234";
	ListValue value2;
	value2.name = "test2";
	value2.number = "12345";
	ListValue firstElement = getElement(list, 0, &errorCode);
	if (errorCode != ok)
	{
		free(list);
		fclose(file);
		return 2;
	}
	if (firstElement.name != "test1" || firstElement.number != "1")
	{
		free(list);
		fclose(file);
		return 3;
	}
	ListValue secondElement = getElement(list, 1, &errorCode);
	if (errorCode != ok)
	{
		free(list);
		fclose(file);
		return 4;
	}
	if (secondElement.name != "test2" || firstElement.number != "2")
	{
		free(list);
		fclose(file);
		return 5;
	}
	free(list);
	fclose(file);
	return ok;
}

int mergeSortTest(void)
{
	List* list = createList();
	if (list == NULL)
	{
		return 1;
	}
	int errorCode = 0;
	mergeSort(&list, true, &errorCode);
	if (errorCode != ok)
	{
		deleteList(&list);
		return 2;
	}
	ListValue* value = calloc(1, sizeof(ListValue));
	if (value == NULL)
	{
		deleteList(&list);
		return 2;
	}
	value->name = "test1";
	value->number = "2";
	if (addElement(list, *value) != ok)
	{
		deleteList(&list);
		free(value);
		return 3;
	}
	ListValue* value2 = calloc(1, sizeof(ListValue));
	if (value2 == NULL)
	{
		deleteList(&list);
		free(value);
		return 3;
	}
	value2->name = "test2";
	value2->number = "1";
	if (addElement(list, *value2) != ok)
	{
		deleteList(&list);
		free(value);
		free(value2);
		return 4;
	}
	mergeSort(&list, true, &errorCode);
	if (errorCode == 0)
	{
		deleteList(&list);
		free(value);
		free(value2);
		return 5;
	}
	ListValue returnValue = getElement(list, 0, &errorCode);
	if (returnValue.name != value->name || returnValue.number != value->number || errorCode != ok)
	{
		deleteList(&list);
		free(value);
		free(value2);
		return 6;
	}
	mergeSort(&list, false, &errorCode);
	if (errorCode != ok)
	{
		deleteList(&list);
		free(value);
		free(value2);
		return 7;
	}
	returnValue = getElement(list, 0, &errorCode);
	if (errorCode != ok || returnValue.name != value2->name || returnValue.number != value2->number)
	{
		deleteList(&list);
		free(value);
		free(value2);
		return 8;
	}
	deleteList(&list);
	free(value);
	free(value2);
	return ok;

}

int tests(void)
{
	int result = mergeSortTest();
	if (result != ok)
	{
		return 10 + result;
	}
	result = readFileTest();
	if (result != ok)
	{
		return 20 + result;
	}
	return ok;
	return ok;
}

int main(void)
{
	int errorCode = tests();
	if (errorCode != tests())
	{
		printf("ERROR IN %s TEST, CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
		return errorCode;
	}
	List* list = createList();
	if (list == NULL)
	{
		printf("MEMORY ERROR\n");
		return memoryError;
	}
	printf("If you want to sort phone book by the name, type 0. Otherwise, type any other number.\n");
	int isByName = 0;
	if (scanf_s("%d", &isByName) != 1)
	{
		printf("INPUT ERROR\n");
		return inputError;
	}
	FILE* file = fopen("phoneBook.txt", "a+");
	if (file == NULL)
	{
		printf("FILE ERROR\n");
		return fileError;
	}
	errorCode = readFile(list, file);
	fclose(file);
	if (errorCode != ok)
	{
		deleteList(list);
		printf("%s\n", ERROR_NAMES[errorCode]);
		return errorCode;
	}
	mergeSort(&list, isByName == 0 ? true: false, &errorCode);
	if (errorCode != ok)
	{
		printf("%s\n", ERROR_NAMES[errorCode]);
		deleteList(list);
		return errorCode;
	}
	for (size_t i = 0; i < getSize(list); ++i)
	{
		printf("%s %s\n", getElement(list, i, &errorCode).number, getElement(list, i, &errorCode).name);
	}
	return ok;
}