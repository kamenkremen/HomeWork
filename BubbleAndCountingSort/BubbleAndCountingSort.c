#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <float.h>

#define TEST_ARRAY_SIZE 100000

int myMax(const int firstNumber, const int secondNumber)
{
    if (firstNumber >= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
}

double myDoubleMax(const double firstNumber, const double secondNumber)
{
    if (firstNumber >= secondNumber)
    {
        return firstNumber;
    }
    return secondNumber;
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
    for (size_t i = 0; i < sizeOfArray; i++)
    {
        for (size_t j = 0; j < sizeOfArray - 1 - i; j++)
        {
            if (array[j] > array[j + 1]) {
                int numberForSwap = array[j];
                array[j] = array[j + 1];
                array[j + 1] = numberForSwap;
            }
        }
    }
}

void countingSort(int* array, const int sizeOfArray)
{

    int maximumElement = INT_MIN;
    int minimumElement = INT_MAX;
    for (size_t i = 0; i < sizeOfArray; i++)
    {
        maximumElement = myMax(array[i], maximumElement);
        minimumElement = myMin(array[i], minimumElement);
    }
    int sizeOfArrayWithNumbersOfNumbers = maximumElement - minimumElement + 1;
    int* arrayWithNumbersOfNumbers = calloc(sizeOfArrayWithNumbersOfNumbers, sizeof(int));
    minimumElement *= -1;
    for (size_t i = 0; i < sizeOfArray; i++)
    {
        arrayWithNumbersOfNumbers[array[i] + minimumElement]++;
    }
    int currentElementInSortedArray = 0;
    for (size_t i = 0; i < sizeOfArrayWithNumbersOfNumbers; i++)
    {
        for (; arrayWithNumbersOfNumbers[i] > 0; arrayWithNumbersOfNumbers[i]--)
        {
            array[currentElementInSortedArray] = (i - minimumElement);
            currentElementInSortedArray++;
        }
    }
    free(arrayWithNumbersOfNumbers);
}

void fillArrayWithRandomNumbers(int* array, const int sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; i++)
    {
        array[i] = rand();
    }
}

double bubbleSortTime(int* array, const int arraySize)
{
    clock_t beforeBubbleSort = clock();
    bubbleSort(array, TEST_ARRAY_SIZE);
    clock_t afterBubbleSort = clock();
    double duration = (double)(afterBubbleSort - beforeBubbleSort) / CLOCKS_PER_SEC;
    return duration;
}

double countingSortTime(int* array, const int arraySize)
{
    clock_t beforeCountingSort = clock();
    countingSort(array, TEST_ARRAY_SIZE);
    clock_t afterCountingSort = clock();
    double duration = (double)(afterCountingSort - beforeCountingSort) / CLOCKS_PER_SEC;
    return duration;
}

void testBubbleSortVSCountingSort(void)
{
    int array[TEST_ARRAY_SIZE] = { 0 };
    fillArrayWithRandomNumbers(array, TEST_ARRAY_SIZE);
    double min = DBL_MAX;
    double max = DBL_MIN;
    double mean = 0;
    for (size_t i = 0; i < 5; i++) 
    {
        fillArrayWithRandomNumbers(array, TEST_ARRAY_SIZE);
        double curentTime = countingSortTime(array, TEST_ARRAY_SIZE);
        mean += curentTime;
        min = myDoubleMin(min, curentTime);
        max = myDoubleMax(max, curentTime);
    }
    mean /= 5;
    printf("Counting sort mean time was %2.5fs and the spread was ~%2.5fs on sorting the random-filled array with size %d\n", mean, myDoubleMax(max - mean, mean - min), TEST_ARRAY_SIZE);
    min = DBL_MAX;
    max = DBL_MIN;
    mean = 0;
    printf("Bubble sort is going to take a minute or two, please wait.\n");
    for (size_t i = 0; i < 5; i++)
    {
        fillArrayWithRandomNumbers(array, TEST_ARRAY_SIZE);
        double curentTime = bubbleSortTime(array, TEST_ARRAY_SIZE);
        mean += curentTime;
        min = myDoubleMin(min, curentTime);
        max = myDoubleMax(max, curentTime);
    }
    mean /= 5;
    printf("Bubble sort mean time was %2.5fs and the spread was ~%2.5fs on sorting the random-filled array with size %d\n", mean, myDoubleMax(max - mean, mean - min), TEST_ARRAY_SIZE);
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
    int* arrayForBubbleSort = malloc(sizeOfArray * sizeof(int));
    int* arrayForCountingSort = malloc(sizeOfArray * sizeof(int));

    for (size_t i = 0; i < sizeOfArray; i++)
    {
        int element = 0;
        scanf_s("%d", &element);
        arrayForBubbleSort[i] = element;
        arrayForCountingSort[i] = element;
    }
    bubbleSort(arrayForBubbleSort, sizeOfArray);
    countingSort(arrayForCountingSort, sizeOfArray);
    printf("Bubble sort: ");
    for (size_t i = 0; i < sizeOfArray; i++)
    {
        printf("%d ", arrayForBubbleSort[i]);
    }
    printf("\nCounting sort: ");
    for (int i = 0; i < sizeOfArray; i++)
    {
        printf("%d ", arrayForCountingSort[i]);
    }
    free(arrayForBubbleSort);
    free(arrayForCountingSort);
    return 0;
}
