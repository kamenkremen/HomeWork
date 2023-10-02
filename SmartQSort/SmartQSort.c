#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

int myMax(int firstNumber, int secondNumber)
{
    if (firstNumber >= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
}

void fillArrayWithRandomNumbers(int array[], int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i >= 0; i--)
    {
        array[i] = rand();
    }
    return 0;
}

void swap(int* firstElement, int* secondElement)
{
    int thirdElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = thirdElement;
    return 0;
}

int insertionSort(int array[], int leftBorder, int rightBorder)
{
    for (int i = leftBorder + 1; i < rightBorder; ++i)
    {
        int j = i;
        while (array[j] < array[j - 1] && j - 1 >= leftBorder)
        {
            swap(&array[j], &array[j - 1]);
            j--;
        }
    }
    return 0;
}

int quickSort(int array[], int leftBorder, int rightBorder)
{
    int splitElement = -1;
    if (rightBorder - leftBorder <= 1)
    {
        return 0;
    }
    if (rightBorder - leftBorder <= 10)
    {
        insertionSort(array, leftBorder, rightBorder);
        return 0;
    }
    for (int i = leftBorder + 1; i < rightBorder; i++)
    {
        if (array[i - 1] != array[i])
        {
            splitElement = myMax(array[i - 1], array[i]);
            break;
        }
    }
    if (splitElement == -1)
    {
        return -1;
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
    return 0;
}

bool isSorted(int array[], int leftBorder, int rightBorder)
{
    for (int i = leftBorder + 1; i < rightBorder; i++)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

bool testForIsSorted(void)
{
    int testArray[100] = { 0 };
    for (int i = 0; i < 100; i++)
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
    return 0;
}

int main()
{
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ОШИБКА %d\n", errorCode);
        return errorCode;
    }
    printf("Ошибок не обнаружено!");
    return 0;
}