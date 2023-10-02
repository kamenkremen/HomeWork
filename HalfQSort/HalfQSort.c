#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#define ARRAY_SIZE 20

void fillArrayWithRandomNumbers(int array[], int sizeOfArray)
{
    for (int i = sizeOfArray - 1; i >= 0; i--)
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
    int firstElementBiggerThanFirst = 0;
    int lastElementBiggerThanFirst = arraySize - 1;
    while (firstElementBiggerThanFirst < lastElementBiggerThanFirst)
    {

        while (array[firstElementBiggerThanFirst] < firstElement)
        {
            firstElementBiggerThanFirst++;
            if (firstElementBiggerThanFirst == arraySize - 1)
            {
                break;
            }
        }
        while (array[lastElementBiggerThanFirst] >= firstElement)
        {
            lastElementBiggerThanFirst--;
            if (lastElementBiggerThanFirst == 0)
            {
                break;
            }
        }
        swap(&array[lastElementBiggerThanFirst], &array[firstElementBiggerThanFirst]);
    }
    swap(&array[firstElementBiggerThanFirst], &array[lastElementBiggerThanFirst]);
}

int main()
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
    return 0;
}