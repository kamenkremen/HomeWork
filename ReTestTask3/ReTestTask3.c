#include <stdlib.h>
#include <stdio.h>

#define INPUT_FILE "input.txt"
#define MAXIMUM_CHAR_SIZE 256


enum ERRORCODES
{
	ok,
	memoryError,
	fileError,
};

int symbolsCount(int* const numberOfAccurances, char* const inputFile)
{
	FILE* file = NULL;
	if (fopen_s(&file, inputFile, "r") != 0)
	{
		return fileError;
	}
	char symbol = 0;
	while ((symbol = fgetc(file)) != EOF)
	{
		const int symbolCode = (int)(symbol);
		++numberOfAccurances[symbolCode];
	}

	fclose(file);
	return ok;
}

int symbolsCountTest(void)
{
	int numberOfAccurances[MAXIMUM_CHAR_SIZE] = { 0 };
	int errorCode = symbolsCount(numberOfAccurances, "test1.txt");
	if (errorCode != ok)
	{
		return fileError;
	}
	if (numberOfAccurances[49] != 1 || numberOfAccurances[50] != 1 || numberOfAccurances[51] != 1 || numberOfAccurances[10] != 1)
	{
		return 3;
	}
	else
	{
		for (size_t i = 0; i < MAXIMUM_CHAR_SIZE; ++i)
		{
			if (i != (int)'1' && i != (int)'2' && i != (int)'3' && i != 10 && numberOfAccurances[i] > 0)
			{
				return 3;
			}
		}
	}
	for (size_t i = 0; i < MAXIMUM_CHAR_SIZE; ++i)
	{
		numberOfAccurances[i] = 0;
	}
	if (symbolsCount(numberOfAccurances, "test2.txt") != ok)
	{
		return fileError;
	}
	for (size_t i = 0; i < MAXIMUM_CHAR_SIZE; ++i)
	{
		if (numberOfAccurances[i] != 0)
		{
			return 4;
		}
	}
	return ok;
}

int tests(void)
{
	if (symbolsCountTest() != ok)
	{
		return 10 + symbolsCountTest();
	}
	return ok;
}


int main(void)
{
	int testsError = tests();
	if (testsError != ok)
	{
		if (testsError == fileError)
		{
			printf("TEST FILE ERROR\n");
			return fileError;
		}
		else 
		{
			printf("SYMBOLS COUNT TEST ERROR, CASE %d\n", testsError % 10);
			return testsError;
		}
	}
	int numberOfAccurances[MAXIMUM_CHAR_SIZE] = { 0 };
	const int errorCode = symbolsCount(numberOfAccurances, INPUT_FILE);
	if (errorCode != ok)
	{
		if (errorCode == fileError)
		{
			printf("FILE ERROR\n");
			return fileError;
		}
	}
	printf("Here is the number of accurances of each symbol in the format <symbol(or it`s code): number of accurances>\n");
	for (size_t i = 0; i < 256; ++i)
	{
		if (numberOfAccurances[i] != 0)
		{
			if (i < 26 || i >= 27 && i < 33 || i == 255)
			{
				printf("Char with the code %d : %d\n", i, numberOfAccurances[i]);
			}
			else
			{
				printf("%c: %d\n", i, numberOfAccurances[i]);
			}
		}
	}
	return ok;
}
