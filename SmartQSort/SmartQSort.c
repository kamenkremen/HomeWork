#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include <locale.h>

#define TEST_ARRAY_SIZE 100
#define TEST_ARRAY_MIN_SIZE 20

const char* TEST_ERRORS[5] = { "", "Insertion sort", "Is sorted function", "Quick sort", "Swap" };

enum ERRORCODES
{
    ok,
    memoryError,
};



int myMax(int firstNumber, int secondNumber)
{
    return firstNumber > secondNumber ? firstNumber : secondNumber;
}

void fillArrayWithRandomNumbers(int* const array, const size_t sizeOfArray)
{
    for (size_t i = sizeOfArray - 1; i != -1; --i)
    {
        array[i] = rand();
    }
}

void swap(int* firstElement, int* secondElement)
{
    int thirdElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = thirdElement;
}

void insertionSort(int* const array, const size_t leftBorder, const size_t rightBorder)
{
    for (size_t i = leftBorder + 1; i < rightBorder; ++i)
    {
        size_t j = i;
        for (size_t j = i; j - 1 >= leftBorder && array[j] < array[j - 1]; --j)
        {
            swap(&array[j], &array[j - 1]);
        }
    }
}

void quickSort(int* const array, const size_t leftBorder, const size_t rightBorder)
{
    if (rightBorder - leftBorder <= 1)
    {
        return;
    }
    if (rightBorder - leftBorder <= 10)
    {
        insertionSort(array, leftBorder, rightBorder);
        return;
    }
    int splitElement = -1;
    for (size_t i = leftBorder + 1; i < rightBorder; ++i)
    {
        if (array[i - 1] != array[i])
        {
            splitElement = myMax(array[i - 1], array[i]);
            break;
        }
    }
    if (splitElement == -1)
    {
        return;
    }
    size_t leftIndex = leftBorder;
    size_t rightIndex = rightBorder - 1;
    while (leftIndex < rightIndex)
    {
        while (array[leftIndex] < splitElement && leftIndex != rightBorder - 1)
        {
            ++leftIndex;
        }
        while (array[rightIndex] >= splitElement && rightIndex != leftBorder)
        {
            --rightIndex;
        }
        swap(&array[rightIndex], &array[leftIndex]);
    }
    swap(&array[leftIndex], &array[rightIndex]);
    size_t splitIndex = leftIndex;
    quickSort(array, leftBorder, splitIndex);
    quickSort(array, splitIndex, rightBorder);
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
    int testArray[TEST_ARRAY_SIZE] = { 0 };
    for (size_t i = 0; i < TEST_ARRAY_SIZE; ++i)
    {
        testArray[i] = i;
    }
    if (!isSorted(testArray, 0, TEST_ARRAY_SIZE))
    {
        return 1;
    }
    swap(&testArray[0], &testArray[1]);
    if (isSorted(testArray, 0, TEST_ARRAY_SIZE))
    {
        return 2;
    }
    testArray[1] = 1;
    if (!isSorted(testArray, 0, TEST_ARRAY_SIZE))
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
    const size_t arraySize = rand() % TEST_ARRAY_SIZE + TEST_ARRAY_MIN_SIZE;
    int* testArray = (int *)calloc(arraySize, sizeof(int));
    fillArrayWithRandomNumbers(testArray, arraySize);
    sort(testArray, 0, arraySize);
    if (!isSorted(testArray, 0, arraySize))
    {
        return 1;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    sort(testArray, 10, arraySize);
    testArray[0] = 100;
    testArray[1] = 1;
    if (!isSorted(testArray, 10, arraySize))
    {
        return 2;
    }
    if (isSorted(testArray, 0, arraySize))
    {
        return 3;
    }
    free(testArray);
    return ok;
}

int tests(void)
{
    if (testForSort(insertionSort) != ok)
    {
        return 10 + testForSort(insertionSort);
    }
    if (testForIsSorted() != ok)
    {
        return 20 + testForIsSorted();
    }
    if (testForSort(quickSort) != ok)
    {
        return 30 + testForSort(insertionSort);
    }
    if (testForSwap() != ok)
    {
        return 41;
    }
    return ok;
}

int main(void)
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("%s ERROR, TEST CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    printf("Ошибок не обнаружено!\n");
    return ok;
}
