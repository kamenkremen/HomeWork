#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#include <memory.h>

#define TEST_ARRAY_SIZE 100000
#define MAX_NUMBER 1000
#define NUMBER_OF_ITERATIONS 5

int myMax(const int firstNumber, const int secondNumber)
{
    return firstNumber > secondNumber ? firstNumber : secondNumber;
}

double myDoubleMax(const double firstNumber, const double secondNumber)
{
    return firstNumber < secondNumber ? firstNumber : secondNumber;
}

double myDoubleMin(const double firstNumber, const double secondNumber)
{
    if (firstNumber <= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
}

int myMin(const int firstNumber, const int secondNumber)
{
    if (firstNumber <= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
}

void bubbleSort(int* array, const int sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        for (size_t j = 0; j < sizeOfArray - 1 - i; ++j)
        {
            if (array[j] > array[j + 1]) {
                int numberForSwap = array[j];
                array[j] = array[j + 1];
                array[j + 1] = numberForSwap;
            }
        }
    }
}

void countingSort(int* const array, const int sizeOfArray)
{

    int maximumElement = INT_MIN;
    int minimumElement = INT_MAX;
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        maximumElement = myMax(array[i], maximumElement);
        minimumElement = myMin(array[i], minimumElement);
    }
    int sizeOfArrayWithNumbersOfNumbers = maximumElement - minimumElement + 1;
    int* arrayWithNumbersOfNumbers = (int*) calloc(sizeOfArrayWithNumbersOfNumbers, sizeof(int));
    minimumElement *= -1;
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        ++arrayWithNumbersOfNumbers[array[i] + minimumElement];
    }
    int currentElementInSortedArray = 0;
    for (size_t i = 0; i < sizeOfArrayWithNumbersOfNumbers; ++i)
    {
        for (; arrayWithNumbersOfNumbers[i] > 0; --arrayWithNumbersOfNumbers[i])
        {
            array[currentElementInSortedArray] = (i - minimumElement);
            ++currentElementInSortedArray;
        }
    }
    free(arrayWithNumbersOfNumbers);
}

void fillArrayWithRandomNumbers(int* array, const int sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % MAX_NUMBER;
    }
}

double sortTime(int* array, const int arraySize, void (*sort) (int*, size_t))
{
    clock_t beforeSort = clock();
    sort(array, TEST_ARRAY_SIZE);
    clock_t afterSort = clock();
    double duration = (double)(afterSort - beforeSort) / CLOCKS_PER_SEC;
    return duration;
}

void testBubbleSortVSCountingSort(void)
{
    int array[TEST_ARRAY_SIZE] = { 0 };
    fillArrayWithRandomNumbers(array, TEST_ARRAY_SIZE);
    int arrayCopy[TEST_ARRAY_SIZE] = { 0 };
    double minBubble = DBL_MAX;
    double maxBubble = DBL_MIN;
    double meanBubble = 0;
    double minCount = DBL_MAX;
    double maxCount = DBL_MIN;
    double meanCount = 0;
    for (size_t i = 0; i < NUMBER_OF_ITERATIONS; ++i) 
    {
        fillArrayWithRandomNumbers(array, TEST_ARRAY_SIZE);
        memcpy(arrayCopy, array, TEST_ARRAY_SIZE);
        double curentTime = sortTime(array, TEST_ARRAY_SIZE, countingSort);
        meanCount += curentTime;
        minCount = myDoubleMin(minCount, curentTime);
        maxCount = myDoubleMax(maxCount, curentTime);
        curentTime = sortTime(arrayCopy, TEST_ARRAY_SIZE, bubbleSort);
        meanBubble += curentTime;
        minBubble = myDoubleMin(minBubble, curentTime);
        maxBubble = myDoubleMax(maxBubble, curentTime);
    }
    meanCount /= NUMBER_OF_ITERATIONS;
    meanBubble /= NUMBER_OF_ITERATIONS;
    printf("Counting sort mean time was %2.5fs and the spread was ~%2.5fs on sorting the random-filled array with size %d\n", meanCount, myDoubleMax(abs(maxCount - meanCount), abs(meanCount - minCount)), TEST_ARRAY_SIZE);
    printf("Bubble sort mean time was %2.5fs and the spread was ~%2.5fs on sorting the random-filled array with size %d\n", meanBubble, myDoubleMax(abs(maxBubble - meanBubble), abs(meanBubble - minBubble)), TEST_ARRAY_SIZE);
}

void printArray(const int* array, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) 
{
    srand(time(NULL));
    printf("Do you wish to sort your array or to compare bubble sort and counting sort?\nType 1  to compare bubble sort and counting sort or any other number to sort your array\n");
    int userAnswer = 0;
    scanf_s("%d", &userAnswer);
    if (userAnswer == 1)
    {
        testBubbleSortVSCountingSort();
        return 0;
    }
    int sizeOfArray = 0;
    printf("Enter the size of array:");
    scanf_s("%d", &sizeOfArray);
    printf("Enter the array:");
    int* arrayForBubbleSort = (int*) malloc(sizeOfArray * sizeof(int));
    int* arrayForCountingSort = (int*) malloc(sizeOfArray * sizeof(int));

    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        int element = 0;
        scanf_s("%d", &element);
        arrayForBubbleSort[i] = element;
        arrayForCountingSort[i] = element;
    }
    bubbleSort(arrayForBubbleSort, sizeOfArray);
    countingSort(arrayForCountingSort, sizeOfArray);
    printf("Bubble sort:\n");
    printArray(arrayForBubbleSort, sizeOfArray);
    printf("\nCounting sort:\n");
    printArray(arrayForCountingSort, sizeOfArray);
    free(arrayForBubbleSort);
    free(arrayForCountingSort);
    return 0;
}
