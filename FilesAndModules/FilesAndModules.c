#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <locale.h>
#include "sortings.h"
#include <string.h>

#define ARRAY_SIZE 100
#define ARRAY_MIN_SIZE 20
#define TEST_ARRAY_SIZE 10
#define MAXIMUM_ELEMENT_IN_ARRAY 50

const char* TEST_ERRORS[6] = { "", "Insertion sort", "Is sorted function", "Quick sort", "Swap", "Most common element" };

enum ERRORCODES
{
    ok,
    memoryError,
};

void fillArrayWithRandomNumbers(int* const array, const size_t sizeOfArray)
{
    for (size_t i = sizeOfArray - 1; i != -1; --i)
    {
        array[i] = rand();
    }
}

bool isSorted(const int* const array, const size_t leftBorder, const size_t rightBorder)
{
    for (size_t i = leftBorder + 1; i < rightBorder; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

int testForIsSorted(void)
{
    int testArray[ARRAY_SIZE] = { 0 };
    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        testArray[i] = i;
    }
    if (!isSorted(testArray, 0, ARRAY_SIZE))
    {
        return 1;
    }
    swap(&testArray[0], &testArray[1]);
    if (isSorted(testArray, 0, ARRAY_SIZE))
    {
        return 2;
    }
    testArray[1] = 1;
    if (!isSorted(testArray, 0, ARRAY_SIZE))
    {
        return 3;
    }
    swap(&testArray[50], &testArray[61]);
    if (isSorted(testArray, 40, 70))
    {
        return 4;
    }
    return ok;
}

bool testForSwap(void)
{
    int first = rand();
    const int secondFirst = first;
    int second = rand();
    const int secondSecond = second;
    swap(&first, &second);
    return !(first == secondSecond && second == secondFirst);
}

int testForSort(void (*sort) (int* const, const size_t, const size_t))
{
    const size_t arraySize = rand() % (ARRAY_SIZE - ARRAY_MIN_SIZE) + ARRAY_MIN_SIZE;
    int* testArray = (int*)calloc(arraySize, sizeof(int));
    if (testArray == NULL)
    {
        return memoryError;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    sort(testArray, 0, arraySize);
    if (!isSorted(testArray, 0, arraySize))
    {
        free(testArray);
        return 1;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    sort(testArray, 10, arraySize);
    testArray[0] = 100;
    testArray[1] = 1;
    if (!isSorted(testArray, 10, arraySize))
    {
        free(testArray);
        return 2;
    }
    if (isSorted(testArray, 0, arraySize))
    {
        free(testArray);
        return 3;
    }
    free(testArray);
    return ok;
}

int findMostCommonElement(int* const array, const size_t arraySize)
{
    quickSort(array, 0, arraySize);
    int maximum = 1;
    int mostCommonElement = array[0];
    int current = 1;
    for (size_t i = 1; i < arraySize; ++i)
    {
        if (array[i] == array[i - 1])
        {
            ++current;
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

int testForFindMostCommonElement(void)
{
    int array[TEST_ARRAY_SIZE] = { 0 };
    if (findMostCommonElement(array, TEST_ARRAY_SIZE) != 0)
    {
        return 1;
    }
    for (size_t i = 0; i < 7; ++i)
    {
        array[i] = 1;
    }
    if (findMostCommonElement(array, TEST_ARRAY_SIZE) != 1)
    {
        return 2;
    }
    for (size_t i = 0; i < 9; ++i)
    {
        array[i] = i;
    }
    array[9] = 8;
    if (findMostCommonElement(array, TEST_ARRAY_SIZE) != 8)
    {
        return 3;
    }
    return ok;
}

int tests(void)
{
    int result = testForSort(insertionSort);
    if (result != ok)
    {
        return 10 + result;
    }
    result = testForIsSorted();
    if (result != ok)
    {
        return 20 + result;
    }
    result = testForSort(quickSort);
    if (result != ok)
    {
        return 30 + result;
    }
    if (testForSwap() != ok)
    {
        return 41;
    }
    result = testForFindMostCommonElement();
    if (result != ok)
    {
        return 50 + result;
    }
    return ok;
}

int main()
{
    srand(time(NULL));
    const int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN %s TEST, CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    const size_t arraySize = rand() % (ARRAY_SIZE - ARRAY_MIN_SIZE) + ARRAY_MIN_SIZE;
    int* array = (int*)calloc(arraySize, sizeof(int));
    if (array == NULL)
    {
        printf("MEMORY ERROR\n");
        free(array);
        return memoryError;
    }
    fillArrayWithRandomNumbers(array, arraySize);
    printf("Array: ");
    for (size_t i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Most common element: %d\n", findMostCommonElement(array, arraySize));
    free(array);
    return ok;
}
