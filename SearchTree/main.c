#include <stdio.h>
#include <stdlib.h>

#include "SearchTree.h"
#include "Test.h"

char* ERRORNAMES[5] = {
	"",
	"Memory error",
	"Null pointer error",
	"No such element",
	"Input error",
};

int finish(Tree** tree, int errorCode)
{
	printf("%s\n", ERRORNAMES[errorCode]);
	deleteTree(tree);
	return errorCode;
}

int main(void)
{
	bool* failedCases = test();
	bool isFailed = false;
	for (size_t i = 0; i < NUMBER_OF_TESTS; ++i)
	{
		if (failedCases[i])
		{
			if (isFailed)
			{
				printf(", %u", i);
			}
			else
			{
				printf("FAILED IN TEST CASES: %u", i);
				isFailed = true;
			}
		}
	}
	if (isFailed)
	{
		printf('\n');
		return testError;
	}
	Tree* tree = createTree();

	while (true)
	{
		printf("Enter 0 to exit the programm.\nEnter 1 to add element.\nEnter 2 to get the value of the key.\n");
		printf("Enter 3 to check if dictionary is containing the key.\nEnter 4 to delete the key and the value from the dictionary.\n");
		int operation = 0;
		if (scanf_s("%d", &operation) != 1 || operation > 4 || operation < 0)
		{
			printf("Incorrect output, enter the number from 1 to 4.\n");
			continue;
		}
		int key = 0;
		int errorCode = ok;
		switch (operation)
		{
			case 0:
				return finish(&tree, 0);
			case 1:
				printf("Enter the key and the value\n");
				char* value = "";
				if (scanf_s("%d", &key) != 1)
				{
					return finish(&tree, inputError);
				}
				value = NULL;
				int length = 1;
				value = (char*)malloc(sizeof(char));
				if (value == NULL)
				{
					return finish(&tree, memoryError);;
				}
				char symbol = 0;
				while ((symbol = getchar()) != '\n') {
					value[length - 1] = symbol;
					length++;
					value = (char*)realloc(value, length);
					if (value == NULL)
					{
						return finish(&tree, memoryError);
					}
				}
				value[length - 1] = '\0';
				errorCode = add(tree, key, value);
				if (errorCode != ok)
				{
					return finish(&tree, errorCode);
				}
				printf("Element added\n");
				break;
			case 2:
				printf("Enter the key\n");
				if (scanf_s("%d", &key) != 1)
				{
					return finish(&tree, inputError);
				}
				errorCode = ok;
				char* outputValue = get(tree, key, &errorCode);
				if (errorCode != ok)
				{
					return finish(&tree, errorCode);
				}
				if (outputValue == NULL)
				{
					printf("No such value\n");
					break;
				}
				printf("Value : %s\n", outputValue);
				break;
			case 3:
				printf("Enter the key\n");
				if (scanf_s("%d", &key) != 1)
				{
					return finish(&tree, inputError);
				}
				errorCode = ok;
				bool containing = contains(tree, key, &errorCode);
				if (errorCode != ok)
				{
					return finish(&tree, errorCode);
				}
				printf("%s\n", containing ? "This key in dictionary" : "This key is not in dictionary");
				break;
			case 4:
				printf("Enter the key\n");
				if (scanf_s("%d", &key) != 1)
				{
					return finish(&tree, inputError);
				}
				errorCode = delete(tree, key);
				if (errorCode == noSuchElement)
				{
					printf("No such element\n");
					break;
				}
				if (errorCode != ok)
				{
					return finish(&tree, errorCode);
				}
				printf("Deleted\n");
				break;
		}
	}
	return ok;
}
