#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>

void fillArrayWithRandomNumbers(int* array, int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i >= 0; i--)
    {
        array[i] = rand() % 1000;
        //добавил ограничение, чтобы увеличить шанс того, что из н и к случайных хотя бы пара совпадет.
    }
}

int myMax(int firstNumber, int secondNumber)
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

int isContained(int* array, int number, int arraySize)
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

bool testForIsContained(void)
{
    int arraySize = rand() % 100 + 20;
    int* testArray = calloc(arraySize, sizeof(int));
    fillArrayWithRandomNumbers(testArray, arraySize);
    if (testArray == NULL)
    {
        free(testArray);
        return false;
    }
    quickSort(testArray, 0, arraySize);
    for (int i = 0; i < arraySize; i++)
    {
        if (i != 0 && testArray[i - 1] + 1 < testArray[i])
        {
            if (isContained(testArray, testArray[i] - 1, arraySize))
            {
                return false;
            }
        }
        if (!isContained(testArray, testArray[i], arraySize))
        {
            return false;
        };
    }
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
    if (!testForIsContained())
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
    printf("Array:");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    quickSort(array, 0, n);
    for (int i = 0; i < k; i++)
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
    free(array);
    return 0;
}