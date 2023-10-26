#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>

enum ERRORCODES
{
    ok,
};


void fillArrayWithRandomNumbers(int* array, const size_t sizeOfArray)
{
    for (size_t i = sizeOfArray - 1; i != -1; --i)
    {
        array[i] = rand() % 1000;
        //добавил ограничение, чтобы увеличить шанс того, что из н и к случайных хотя бы пара совпадет.
    }
}

int myMax(const int firstNumber, const int secondNumber)
{
    if (firstNumber >= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
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
            --j;
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
    int leftIndex = leftBorder;
    int rightIndex = rightBorder - 1;
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
    int splitIndex = leftIndex;
    quickSort(array, leftBorder, splitIndex);
    quickSort(array, splitIndex, rightBorder);
    return 0;
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

bool isContained(int* array, int number, const size_t arraySize)
{
    int leftBorder = 0;
    int rightBorder = arraySize;
    while (leftBorder + 1 < rightBorder)
    {
        int middle = (leftBorder + rightBorder) / 2;
        if (array[middle] > number)
        {
            rightBorder = middle;
        }
        else
        {
            leftBorder = middle;
        }
    }
    return array[leftBorder] == number;
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
    int* testArray = calloc(arraySize, sizeof(int));
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

int testForIsContained(void)
{
    const size_t arraySize = rand() % 100 + 20;
    int* testArray = calloc(arraySize, sizeof(int));
    fillArrayWithRandomNumbers(testArray, arraySize);
    if (testArray == NULL)
    {
        free(testArray);
        return 1;
    }
    quickSort(testArray, 0, arraySize);
    for (size_t i = 0; i < arraySize; ++i)
    {
        if (i != 0 && testArray[i - 1] + 1 < testArray[i])
        {
            if (isContained(testArray, testArray[i] - 1, arraySize))
            {
                return 2;
            }
        }
        if (!isContained(testArray, testArray[i], arraySize))
        {
            return 3;
        };
    }
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
        return 30 + testForSort(quickSort);
    }
    if (testForSwap())
    {
        return 4;
    }
    if (testForIsContained() != ok)
    {
        return 50 + testForIsContained();
    }
    return ok;
}

int main(void)
{
    srand(time(NULL));
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ERROR %d\n", errorCode);
        return errorCode;
    }
    int n = 0;
    printf("Enter the size of the array:");
    scanf_s("%d", &n);
    int k = 0;
    printf("Enter the amount of numbers:");
    scanf_s("%d", &k);
    int* array = calloc(n, sizeof(int));
    if (array == NULL)
    {
        printf("ERROR");
        free(array);
        return 1;
    }
    fillArrayWithRandomNumbers(array, n);
    printf("Array:\n");
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    quickSort(array, 0, n);
    for (size_t i = 0; i < k; ++i)
    {
        int number = rand() % 1000;
        if (isContained(array, number, n))
        {
            printf("%d is contained in the array.\n", number);
        }
        else
        {
            printf("%d isn`t contained in the array.\n", number);
        }
    }
    printf("\n");
    free(array);
    return 0;
}