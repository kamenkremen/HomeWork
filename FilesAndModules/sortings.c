#include "sortings.h"
#include <stdlib.h>

enum ERRORCODES
{
    ok,
    memoryError,
};

static int myMax(const int firstNumber, const int secondNumber)
{
    return firstNumber > secondNumber ? firstNumber : secondNumber;
}

static void swap(int* const firstElement, int* const secondElement)
{
    const int thirdElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = thirdElement;
}

void insertionSort(int* const array, const size_t leftBorder, const size_t rightBorder)
{
    for (size_t i = leftBorder + 1; i < rightBorder; ++i)
    {
        for (size_t j = i; j > leftBorder && array[j] < array[j - 1]; --j)
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
    quickSort(array, leftBorder, leftIndex);
    quickSort(array, leftIndex, rightBorder);
}
