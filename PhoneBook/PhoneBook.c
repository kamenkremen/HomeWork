#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <malloc.h>

/*#include "Files.h"

bool isTwoArraysEqual(char** const array1, char** const array2, int const size)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (strcmp(array1[i], array2[i]))
		{
			return false;
		}
	}
	return true;
}



void findNameByNumber(char** const numbers, char** const names, int* foundedNumbers, char* const number, int const amountOfRecordings)
{
	int current = 0;
	for (size_t i = 0; i < amountOfRecordings; ++i)
	{
		if (!strcmp(number, numbers[i]))
		{
			foundedNumbers[current] = i + 1;
			++current;
		}
	}
}

void findNumberByName(char** const numbers, char** const names, int* foundedNames, char* const name, int const amountOfRecordings)
{
	int current = 0;
	for (size_t i = 0; i < amountOfRecordings; ++i)
	{
		if (!strcmp(name, names[i]))
		{
			foundedNames[current] = i + 1;
			++current;
		}
	}
}

int readFileAndParseDataTest(void)
{
	FILE* file = fopen("test1.txt", "r");
	if (file == NULL)
	{
		fclose(file);
		return 31;
	}
	char* data[5] = { 0 };
	int stringsRead  = readFile(data, file);
	fclose(file);
	if (stringsRead < 0)
	{
		for (size_t i = 0; i < 5; ++i)
		{
			free(data[i]);
		}
		return 31;
	}
	char* supposedData[5] = { "88005553535$test1", "2222222222222$test2", "3$test3", "4$test4", "89082191077$test5" };
	if (!isTwoArraysEqual(data, supposedData, 5))
	{
		for (size_t i = 0; i < 5; ++i)
		{
			free(data[i]);
		}
		return 31;
	}
	char* numbers[5] = { 0 };
	char* names[5] = { 0 };
	char* supposedNumbers[5] = { "88005553535", "2222222222222", "3", "4", "89082191077" };
	char* supposedNames[5] = { "test1", "test2", "test3", "test4", "test5" };
	if (parseData(numbers, names, data, 5) < 0)
	{
		for (size_t i = 0; i < 5; ++i)
		{
			free(data[i]);
			free(numbers[i]);
			free(names[i]);
		}
		return 41;
	}
	if (!isTwoArraysEqual(numbers, supposedNumbers, 5) || !isTwoArraysEqual(names, supposedNames, 5))
	{
		for (size_t i = 0; i < 5; ++i)
		{
			free(data[i]);
			free(numbers[i]);
			free(names[i]);
		}
		return 41;
	}
	for (size_t i = 0; i < 5; ++i)
	{
		free(data[i]);
		free(numbers[i]);
		free(names[i]);
	}

	return 0;
}

int findNameByNumberTest(void)
{
	char* numbers[5] = { "1", "2", "3", "4", "5" };
	char* names[5] = { "name1", "name2", "name3", "name4", "name5" };
	int foundedNumber[5] = { 0 };
	for (size_t i = 0; i < 5; ++i)
	{
		findNameByNumber(numbers, names, foundedNumber, numbers[i], 5);
		if (foundedNumber[0] - 1 != i)
		{
			return 1;
		}
	}
	foundedNumber[0] = 0;
	findNameByNumber(numbers, names, foundedNumber, "6", 5);
	if (foundedNumber[0] != 0)
	{
		return 2;
	}
	return 0;
}

int findNumberByNameTest(void)
{
	char* numbers[5] = { "1", "2", "3", "4", "5" };
	char* names[5] = { "name1", "name2", "name3", "name4", "name5" };
	int foundedName[5] = { 0 };
	for (size_t i = 0; i < 5; ++i)
	{
		findNumberByName(numbers, names, foundedName, names[i], 5);
		if (foundedName[0] - 1 != i)
		{
			return 1;
		}
	}
	foundedName[0] = 0;
	findNameByNumber(numbers, names, foundedName, "6", 5);

	if (foundedName[0] != 0)
	{
		printf("%d\n", foundedName[0]);
		return 2;
	}
	return 0;
}

int tests(void)
{
	if (findNumberByNameTest() != 0)
	{
		return 10 + findNumberByNameTest();
	}
	if (findNameByNumberTest() != 0)
	{
		return 20 + findNameByNumberTest();
	}
	if (readFileAndParseDataTest() != 0)
	{
		return readFileAndParseDataTest();
	}
	return 0;
}

char** parseNumbers(const char* const phoneBook)
{
	size_t length = strlen(phoneBook);
	char* current = (char*)calloc(1, sizeof(char));
	if (current == NULL)
	{
		return NULL;
	}
	char** parsed = (char**)calloc(100, sizeof(char*));
	if (parsed == NULL)
	{
		free(current);
		return NULL;
	}
	size_t capacity = 1;
	size_t size = 0;
	size_t parsedSize = 0;
	bool isNumber = true;
	for (size_t i = 0; i < length; ++i)
	{
		if (phoneBook[i] == '\n')
		{
			isNumber = true;
			continue;
		}
		if (!isNumber)
		{
			continue;
		}
		if (phoneBook[i] == '&')
		{
			parsed[parsedSize] = current;
			++parsedSize;
			current = (char*)calloc(1, sizeof(char));
			if (current == NULL)
			{
				for (size_t j = 0; j < parsedSize; ++j)
				{
					free(parsed[j]);
				}
				free(parsed);
				return NULL;
			}
			capacity = 1;
			size = 0;
			isNumber = false;
		}
		if (size >= current)
		{
			capacity *= 2;
			char* buffer = (char*)realloc(current, capacity);
			free(current);
			if (buffer == NULL)
			{
				for (size_t j = 0; j < parsedSize; ++j)
				{
					free(parsed[j]);
				}
				free(parsed);
				return NULL;
			}
		}
	}
}*/

int main(void)
{
	printf("%d, %d, %d, %d", sizeof(short), sizeof(int), sizeof(long int), sizeof(long long));
	return 0;
}