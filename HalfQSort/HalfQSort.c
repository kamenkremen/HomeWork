#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define ARRAY_SIZE 20

void fillArrayWithRandomNumbers(int* array, const int sizeOfArray)
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

void halfQSort(int* array, const int arraySize)
{
    int firstElement = array[0];
    int leftIndex = 0;
    int rightIndex = arraySize - 1;
    while (leftIndex < rightIndex)
    {

        while (array[leftIndex] < firstElement && leftIndex != arraySize - 1)
        {
            ++leftIndex;
        }
        while (array[rightIndex] >= firstElement && rightIndex != 0)
        {
            --rightIndex;
        }
        swap(&array[rightIndex], &array[leftIndex]);
    }
    swap(&array[leftIndex], &array[rightIndex]);
}

int main(void)
{
    srand(time(NULL));
    int array[ARRAY_SIZE] = { 0 };
    fillArrayWithRandomNumbers(array, ARRAY_SIZE);
    int firstElement = array[0];
    printf("First element: %d\n", firstElement);
    halfQSort(array, ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}
