#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>

int myMax(int firstNumber, int secondNumber)
{
    if (firstNumber >= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
}

void fillArrayWithRandomNumbers(int* array, int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i >= 0; --i)
    {
        array[i] = rand() % 100; //добавил ограничение, чтобы увеличить шанс того, что в массиве несколько элементов совпадут.
    }
}

void swap(int* firstElement, int* secondElement)
{
    int thirdElement = *firstElement;
    *firstElement = *secondElement;
    *secondElement = thirdElement;
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
    for (int i = leftBorder + 1; i < rightBorder; ++i)
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
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ERROR %d\n", errorCode);
        return errorCode;
    }
    int arraySize = rand() % 100 + 20;
    int* array = calloc(arraySize, sizeof(int));
    if (array == NULL)
    {
        printf("ERROR");
        free(array);
        return 1;
    }
    fillArrayWithRandomNumbers(array, arraySize);
    printf("Array: ");
    for (int i = 0; i < arraySize; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    int mostCommonElement = findMostCommonElement(array, arraySize);
    printf("Most common element: %d", mostCommonElement);
    free(array);
    return 0;
}