#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>
#include <locale.h>

enum ERRORCODES
{
    ok,
    memoryError,
};

int myMax(int firstNumber, int secondNumber)
{
    if (firstNumber >= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
}

void fillArrayWithRandomNumbers(int* array, const size_t sizeOfArray)
{
    for (size_t i = sizeOfArray - 1; i != -1; i--)
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

void insertionSort(int* array, const int leftBorder, const int rightBorder)
{
    for (size_t i = leftBorder + 1; i < rightBorder; ++i)
    {
        size_t j = i;
        while (j - 1 >= leftBorder && array[j] < array[j - 1])
        {
            swap(&array[j], &array[j - 1]);
            j--;
        }
    }
}

void quickSort(int* array, const int leftBorder, const int rightBorder)
{
    int splitElement = -1;
    if (rightBorder - leftBorder <= 1)
    {
        return;
    }
    if (rightBorder - leftBorder <= 10)
    {
        insertionSort(array, leftBorder, rightBorder);
        return;
    }
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
    int firstElementBiggerThanSplit = leftBorder;
    int lastElementBiggerThanSplt = rightBorder - 1;
    while (firstElementBiggerThanSplit < lastElementBiggerThanSplt)
    {

        while (array[firstElementBiggerThanSplit] < splitElement)
        {
            firstElementBiggerThanSplit++;
            if (firstElementBiggerThanSplit == rightBorder - 1)
            {
                break;
            }
        }
        while (array[lastElementBiggerThanSplt] >= splitElement)
        {
            lastElementBiggerThanSplt--;
            if (lastElementBiggerThanSplt == leftBorder)
            {
                break;
            }
        }
        swap(&array[lastElementBiggerThanSplt], &array[firstElementBiggerThanSplit]);
    }
    swap(&array[firstElementBiggerThanSplit], &array[lastElementBiggerThanSplt]);
    int splitIndex = firstElementBiggerThanSplit;
    quickSort(array, leftBorder, splitIndex);
    quickSort(array, splitIndex, rightBorder);
}

bool isSorted(int* array, const int leftBorder, const int rightBorder)
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
    int testArray[100] = { 0 };
    for (size_t i = 0; i < 100; ++i)
    {
        testArray[i] = i;
    }
    if (!isSorted(testArray, 0, 100))
    {
        return 1;
    }
    swap(&testArray[0], &testArray[1]);
    if (isSorted(testArray, 0, 100))
    {
        return 2;
    }
    testArray[1] = 1;
    if (!isSorted(testArray, 0, 100))
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

int testForSort(void (*sort) (int*, int, int))
{
    const size_t arraySize = rand() % 100 + 20;
    int* testArray =(int *) calloc(arraySize, sizeof(int));
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
        return 4;
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
        printf("ОШИБКА %d\n", errorCode);
        return errorCode;
    }
    printf("Ошибок не обнаружено!");
    return 0;
}