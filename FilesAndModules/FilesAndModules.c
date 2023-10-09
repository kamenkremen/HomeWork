#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <locale.h>
#include "sortings.h"
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS 1

void fillArrayWithRandomNumbers(int* array, int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i >= 0; --i)
    {
        array[i] = rand() % 100; //добавил ограничение, чтобы увеличить шанс того, что в массиве несколько элементов совпадут.
    }
}

int findMostCommonElement(int* array, int arraySize)
{
    quickSort(array, 0, arraySize);
    int maximum = 1;
    int mostCommonElement = array[0];
    int current = 1;
    for (int i = 1; i < arraySize; ++i)
    {
        if (array[i] == array[i - 1])
        {
            current++;
        }
        else
        {
            if (maximum < current)
            {
                mostCommonElement = array[i - 1];
                maximum = current;
            }
            current = 1;
        }
    }
    if (maximum < current)
    {
        mostCommonElement = array[arraySize - 1];
        maximum = current;
    }
    return mostCommonElement;
}

bool isSorted(int array[], int leftBorder, int rightBorder)
{
    for (int i = leftBorder + 1; i < rightBorder; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

bool testForFindMostCommonElement(void)
{
    int array[10] = { 0 };
    if (findMostCommonElement(array, 10) != 0)
    {
        return false;
    }
    for (int i = 0; i < 7; ++i)
    {
        array[i] = 1;
    }
    if (findMostCommonElement(array, 10) != 1)
    {
        return false;
    }
    for (int i = 0; i < 9; ++i)
    {
        array[i] = i;
    }
    array[9] = 8;
    if (findMostCommonElement(array, 10) != 8)
    {
        return false;
    }
    return true;
}

bool testForIsSorted(void)
{
    int testArray[100] = { 0 };
    for (int i = 0; i < 100; ++i)
    {
        testArray[i] = i;
    }
    if (!isSorted(testArray, 0, 100))
    {
        return false;
    }
    swap(&testArray[0], &testArray[1]);
    if (isSorted(testArray, 0, 100))
    {
        return false;
    }
    testArray[1] = 1;
    if (!isSorted(testArray, 0, 100))
    {
        return false;
    }
    swap(&testArray[50], &testArray[61]);
    if (isSorted(testArray, 40, 70))
    {
        return false;
    }
    return true;
}

bool testForSwap(void)
{
    int first = rand();
    int secondFirst = first;
    int second = rand();
    int secondSecond = second;
    swap(&first, &second);
    if (first == secondSecond && second == secondFirst)
    {
        return true;
    }
    return false;
}

bool testForInsertionSort(void)
{
    int arraySize = rand() % 100 + 20;
    int* testArray = calloc(arraySize, sizeof(int));
    fillArrayWithRandomNumbers(testArray, arraySize);
    insertionSort(testArray, 0, arraySize);
    if (!isSorted(testArray, 0, arraySize))
    {
        return false;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    insertionSort(testArray, 10, arraySize);
    testArray[0] = 100;
    testArray[1] = 1;
    if (!isSorted(testArray, 10, arraySize))
    {
        return false;
    }
    if (isSorted(testArray, 0, arraySize))
    {
        return false;
    }
    free(testArray);
    return true;
}

bool testForQuickSort(void)
{
    int arraySize = rand() % 100 + 20;
    int* testArray = calloc(arraySize, sizeof(int));
    fillArrayWithRandomNumbers(testArray, arraySize);
    quickSort(testArray, 0, arraySize);
    if (!isSorted(testArray, 0, arraySize))
    {
        return false;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    quickSort(testArray, 10, arraySize);
    testArray[0] = 100;
    testArray[1] = 1;
    if (!isSorted(testArray, 10, arraySize))
    {
        return false;
    }
    if (isSorted(testArray, 0, arraySize))
    {
        return false;
    }
    free(testArray);
    return true;
}

int tests(void)
{
    if (!testForInsertionSort())
    {
        return 1;
    }
    if (!testForIsSorted())
    {
        return 2;
    }
    if (!testForQuickSort())
    {
        return 3;
    }
    if (!testForSwap())
    {
        return 4;
    }
    if (!testForFindMostCommonElement())
    {
        return 5;
    }
    return 0;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    printf("Обработаны будут только первые 10000 элементов входного файла input.txt, вводить числа нужно через запятую.\n");
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ERROR %d\n", errorCode);
        return errorCode;
    }
    FILE* file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Файл не найден.");
        return 1;
    }
    int linesRead = 0;
    char symbol = 0;
    //char* data = malloc(100 * sizeof(char)); я не понимаю почему, но если я выделяю память с использованием malloc - программа падает.
    char data[10001] = { 0 };
    int amountOfNumbers = 1;
    int amountOfSymbols = 0;
    while ((symbol = fgetc(file)) != EOF && amountOfSymbols < 10000)
    {
        ++amountOfSymbols;
        if (symbol == ',')
        {
            ++amountOfNumbers;
        }
        strncat(data, &symbol, 1);
    }
    fclose(file);
    int* array = calloc(amountOfNumbers, sizeof(int));
    int currentNumber = 0;
    int number = 0;
    for (int i = 0; i < strlen(data); ++i)
    {
        if (data[i] == ',')
        {
            array[currentNumber] = number;
            ++currentNumber;
            number = 0;
            continue;
        }
        if (data[i] != '1' && data[i] != '2' && data[i] != '3' && data[i] != '4' && data[i] != '5' && data[i] != '6' && data[i] != '7' && data[i] != '8' && data[i] != '9' && data[i] != '0')
        {
            continue;
        }
        number *= 10;
        number += data[i] - '0';
    }
    array[currentNumber] = number;

    int mostCommonElement = findMostCommonElement(array, amountOfNumbers);
    printf("Самый часто встречающийся элемент: %d", mostCommonElement);
    free(array);
    return 0;
}