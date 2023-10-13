#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <malloc.h>

#define DATA_SIZE 101
#define NUMBER_LENGTH 90
#define NAME_LENGTH 900

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

int readFile(char** data, FILE* const file)
{
	int currentString = 0;
	char buffer[1000] = "";
	while (fscanf(file, "%s", buffer) == 1)
	{
		data[currentString] = (char *) malloc(strlen(buffer) * sizeof(char) + 2);
		if (data[currentString] == NULL)
		{
			for (size_t i = 0; i <= currentString; ++i)
			{
				free(data[i]);
			}
			return -1;
		}
		if (strcpy(data[currentString], buffer) == NULL)
		{
			for (size_t i = 0; i <= currentString; ++i)
			{
				free(data[i]);
			}
			return -1;
		}
		++currentString;
	}
	return currentString;
}

int parseData(char** numbers, char** names, char** data, int const numberOfStrings)
{
	for (size_t i = 0; i < numberOfStrings; ++i)
	{
		numbers[i] = malloc(sizeof(char) * NUMBER_LENGTH);
		names[i] = malloc(sizeof(char) * NAME_LENGTH);
		if (numbers[i] == NULL || names[i] == NULL)
		{
			for (size_t j = 0; j <= numberOfStrings; ++j)
			{
				free(data[j]);
				if (j <= i)
				{
					free(numbers[j]);
					free(names[j]);
				}
			}
			return -1;
		}
	}
	int currentNumber = 0;
	for (size_t i = 0; i < numberOfStrings; ++i)
	{
		size_t separator = 0;
		char number[NUMBER_LENGTH] = "";
		char name[NAME_LENGTH] = "";
		for (size_t j = 0; j < strlen(data[i]); ++j)
		{
			if (data[i][j] == '$')
			{
				separator = j;
				break;
			}
		}
		if (strncat(number, data[i], separator) == NULL)
		{
			for (size_t j = 0; j <= numberOfStrings; ++j)
			{
				free(data[j]);
				if (j <= i)
				{
					free(numbers[j]);
					free(names[j]);
				}
			}
			return -2;
		}
		for (size_t j = separator + 1; j < strlen(data[i]); ++j)
		{
			if (strncat(name, &data[i][j], 1) == NULL)
			{
				for (size_t z = 0; z <= numberOfStrings; ++z)
				{
					free(data[z]);
					if (z <= i)
					{
						free(numbers[z]);
						free(names[z]);
					}
				}
				return -2;
			}
		}
		++currentNumber;
		if (strcpy(numbers[i], number) == NULL)
		{
			for (size_t j = 0; j <= numberOfStrings; ++j)
			{
				free(data[j]);
				if (j <= i)
				{
					free(numbers[j]);
					free(names[j]);
				}
			}
			return -2;
		};
		if (strcpy(names[i], name) == NULL)
		{
			for (size_t j = 0; j <= numberOfStrings; ++j)
			{
				free(data[j]);
				if (j <= i)
				{
					free(numbers[j]);
					free(names[j]);
				}
			}
			return -2;
		}
	}
	return currentNumber;
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
		for (int i = 0; i < 5; ++i)
		{
			free(data[i]);
		}
		return 31;
	}
	char* supposedData[5] = { "88005553535$test1", "2222222222222$test2", "3$test3", "4$test4", "89082191077$test5" };
	if (!isTwoArraysEqual(data, supposedData, 5))
	{
		for (int i = 0; i < 5; ++i)
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
		for (int i = 0; i < 5; ++i)
		{
			free(data[i]);
			free(numbers[i]);
			free(names[i]);
		}
		return 41;
	}
	if (!isTwoArraysEqual(numbers, supposedNumbers, 5) || !isTwoArraysEqual(names, supposedNames, 5))
	{
		for (int i = 0; i < 5; ++i)
		{
			free(data[i]);
			free(numbers[i]);
			free(names[i]);
		}
		return 41;
	}
	for (int i = 0; i < 5; ++i)
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

int main(void)
{
	setlocale(LC_ALL, "Russian");
	if (tests() != 0)
	{
		printf("ОШИБКА %d\n", tests());
		return 1;
	}
	FILE* file = fopen("phoneBook.txt", "a+");
	if (file == NULL)
	{
		file = fopen("phoneBook.txt", "w+");
		fclose(file);
		file = fopen("phoneBook.txt", "a+");
	}
	char* numbers[DATA_SIZE] = { 0 };
	char* names[DATA_SIZE] = { 0 };
	char* data[DATA_SIZE] = { 0 };
	int numberOfStrings = readFile(data, file);
	if (numberOfStrings < 0)
	{
		printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ");
		fclose(file);
		return 1;
	}

	int amountOfRecordings = parseData(numbers, names, data, numberOfStrings);
	if (amountOfRecordings < 0)
	{
		printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ");
		fclose(file);
		return 1;
	}
	for (size_t j = 0; j < numberOfStrings; ++j)
	{
		free(data[j]);
	}
	int numberBeforeChanges = amountOfRecordings;
	while (true)
	{
		printf("Введите номер операции:\n");
		int command = -1;
		if (scanf("%d", &command) != 1)
		{
			printf("Некорректный номер");
			return 1;
		}
		if (command == 0)
		{
			fclose(file);
			printf("До новых встреч!\n");
			for (size_t i = 0; i < amountOfRecordings; ++i)
			{
				free(names[i]);
				free(numbers[i]);
			}

			return 0;
		}
		if (command == 1)
		{
			printf("Введите имя:\n");
			names[amountOfRecordings] = malloc(NAME_LENGTH * sizeof(char));
			if (names[amountOfRecordings] == NULL)
			{
				for (size_t i = 0; i < amountOfRecordings; ++i)
				{
					free(names[i]);
					free(numbers[i]);
				}
				free(names[amountOfRecordings]);
				printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n");
				return 1;
			}
			while (1)
			{
				if (scanf_s("%s", names[amountOfRecordings], NAME_LENGTH - 2) != 1)
				{
					printf("ОШИБКА ВВОДА\n");
					for (size_t i = 0; i < amountOfRecordings; ++i)
					{
						free(names[i]);
						free(numbers[i]);
					}
					free(names[amountOfRecordings]);
					return 1;
				}
				bool is$Contained = false;
				for (size_t i = 0; i < strlen(names[amountOfRecordings]); ++i)
				{
					if (names[amountOfRecordings][i] == '$')
					{
						is$Contained = true;
						break;
					}
				}
				if (!is$Contained)
				{
					break;
				}
				printf("Имя не должно содержать символ $. Повторите ввод.\n");
			}
			printf("Введите номер:\n");
			numbers[amountOfRecordings] = malloc(NUMBER_LENGTH * sizeof(char));
			if (numbers[amountOfRecordings] == NULL)
			{
				for (size_t i = 0; i <= amountOfRecordings; ++i)
				{
					free(names[i]);
					free(numbers[i]);
				}
				printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ\n");
				fclose(file);
				return 1;
			}
			while (1)
			{
				if (scanf_s("%s", numbers[amountOfRecordings], NUMBER_LENGTH - 2) != 1)
				{
					printf("Ошибка ввода!\n");
					fclose(file);
					printf("До новых встреч!\n");
					for (size_t i = 0; i < amountOfRecordings; ++i)
					{
						free(names[i]);
						free(numbers[i]);
					}
					return 1;
				}
				bool is$Contained = false;
				for (size_t i = 0; i < strlen(numbers[amountOfRecordings]); ++i)
				{
					if (numbers[amountOfRecordings][i] == '$')
					{
						is$Contained = true;
						break;
					}
				}
				if (!is$Contained)
				{
					break;
				}
				printf("Номер не должен содержать символ $. Повторите ввод.\n");
			}
			++amountOfRecordings;
		}
		if (command == 2)
		{
			for (size_t i = 0; i < amountOfRecordings; ++i)
			{
				printf("Номер - %s, Имя - %s\n", numbers[i], names[i]);
			}
			printf("\n");
		}
		if (command == 3)
		{
			printf("Введите имя:\n");
			char name[NAME_LENGTH] = "";
			if (scanf_s("%s", name, NAME_LENGTH - 2) != 1)
			{
				printf("ОШИБКА ВВОДА\n");
				fclose(file);
				printf("До новых встреч!\n");
				for (size_t i = 0; i <= amountOfRecordings; ++i)
				{
					free(names[i]);
					free(numbers[i]);
				}
				return 1;
			};
			int foundedNames[DATA_SIZE] = { 0 };
			findNumberByName(numbers, names, foundedNames, name, amountOfRecordings);
			if (foundedNames[0] == 0)
			{
				printf("Номер не найден!\n");
				continue;
			}
			for (size_t i = 0; i < DATA_SIZE && foundedNames[i] > 0; ++i)
			{
				printf("Найден номер - %s\n", numbers[foundedNames[i] - 1]);
			}
		}
		if (command == 4)
		{
			printf("Введите номер:\n");
			char number[NUMBER_LENGTH] = "";
			if (scanf_s("%s", number, NUMBER_LENGTH) != 1)
			{
				printf("ОШИБКА ВВОДА");
				fclose(file);
				printf("До новых встреч!\n");
				for (size_t i = 0; i <= amountOfRecordings; ++i)
				{
					free(names[i]);
					free(numbers[i]);
				}
				return 1;
			};
			int foundedNumbers[DATA_SIZE] = { 0 };
			findNameByNumber(numbers, names, foundedNumbers, number, amountOfRecordings);
			if (foundedNumbers[0] == 0)
			{
				printf("Имя не найдено!\n");
				continue;
			}
			for (size_t i = 0; i < DATA_SIZE && foundedNumbers[i] > 0; ++i)
			{
				printf("Найдено имя - %s\n", names[foundedNumbers[i] - 1]);
			}

		}
		if (command == 5)
		{
			for (size_t i = numberBeforeChanges; i < amountOfRecordings; ++i)
			{
				if (fprintf(file, "%s$%s\n", numbers[i], names[i]) < 0)
				{
					printf("ОШИБКА ЗАПИСИ В ФАЙЛ");
					fclose(file);
					for (size_t i = 0; i <= amountOfRecordings; ++i)
					{
						free(names[i]);
						free(numbers[i]);
					}
					return 1;
				};
			} 
			printf("Успешно записано в файл!\n");
		}
	}
	return 0;
}