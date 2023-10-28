#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TEST_ARRAY_SIZE 100
#define TEST_ARRAY_MIN_SIZE 20
#define MAXIMUM_NUMBER_IN_ARRAY 1000

enum ERRORCODES
{
    ok,
    memoryError,
};

const char* TESTS_ERROR[6] = { "ok", "insertion sort", "is sorted function", "quick sort", "swap", "is contained" };

void fillArrayWithRandomNumbers(int* const array, const size_t sizeOfArray)
{
    for (size_t i = sizeOfArray - 1; i != -1; --i)
    {
        array[i] = rand() % MAXIMUM_NUMBER_IN_ARRAY;
        //добавил ограничение, чтобы увеличить шанс того, что из н и к случайных хотя бы пара совпадет.
    }
}

int myMax(const int firstNumber, const int secondNumber)
{
    return firstNumber > secondNumber ? firstNumber : secondNumber;
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

bool isContained(const int* const array, const int number, const size_t arraySize)
{
    size_t leftBorder = 0;
    size_t rightBorder = arraySize;
    while (leftBorder + 1 < rightBorder)
    {
        size_t middle = (leftBorder + rightBorder) / 2;
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
    const size_t arraySize = rand() % (TEST_ARRAY_SIZE - TEST_ARRAY_MIN_SIZE) + TEST_ARRAY_MIN_SIZE;
    int* testArray = (int*)calloc(arraySize, sizeof(int));
    if (testArray == NULL)
    {
        free(testArray);
        return memoryError;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    sort(testArray, 0, arraySize);
    if (!isSorted(testArray, 0, arraySize))
    {
        free(testArray);
        return 2;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    sort(testArray, 10, arraySize);
    testArray[0] = 100;
    testArray[1] = 1;
    if (!isSorted(testArray, 10, arraySize))
    {
        free(testArray);
        return 3;
    }
    if (isSorted(testArray, 0, arraySize))
    {
        free(testArray);
        return 4;
    }
    free(testArray);
    return ok;
}

int testForIsContained(void)
{
    const size_t arraySize = rand() % (TEST_ARRAY_SIZE - TEST_ARRAY_MIN_SIZE) + TEST_ARRAY_MIN_SIZE;
    int* testArray = (int*)calloc(arraySize, sizeof(int));
    if (testArray == NULL)
    {
        return memoryError;
    }
    fillArrayWithRandomNumbers(testArray, arraySize);
    quickSort(testArray, 0, arraySize);
    for (size_t i = 0; i < arraySize; ++i)
    {
        if (i != 0 && testArray[i - 1] + 1 < testArray[i])
        {
            if (isContained(testArray, testArray[i] - 1, arraySize))
            {
                free(testArray);
                return 2;
            }
        }
        if (!isContained(testArray, testArray[i], arraySize))
        {
            free(testArray);
            return 3;
        };
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
    const int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN %s TESTS, CASE %d\n", TESTS_ERROR[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    int n = 0;
    printf("Enter the size of the array:");
    scanf_s("%d", &n);
    int k = 0;
    printf("Enter the amount of numbers:");
    scanf_s("%d", &k);
    int* array = (int*) calloc(n, sizeof(int));
    if (array == NULL)
    {
        printf("MEMORY ERROR");
        free(array);
        return memoryError;
    }
    fillArrayWithRandomNumbers(array, n);
    printf("Array:\n");
    for (size_t i = 0; i < n; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    quickSort(array, 0, n);
    for (size_t i = 0; i < k; ++i)
    {
        const int number = rand() % MAXIMUM_NUMBER_IN_ARRAY;
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
