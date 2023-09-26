#include <stdio.h>
#include <stdlib.h>

void swapTwoElements(int array[], int firstElement, int secondElement)
{
    int thirdElement = array[firstElement];
    array[firstElement] = array[secondElement];
    array[secondElement] = thirdElement;
}

void reverseSubarray(int array[], int leftBorder, int rightBorder)
{
    for (int i = 0; i < (rightBorder - leftBorder) / 2 + 1; i++)
    {
        swapTwoElements(array, i + leftBorder, rightBorder - i);
    }
}

void swapFirstNElementsAndLastMElements(int array[], int lengthOfTheFirstSubarray, int lengthOfTheSecondSubarray)
{
    reverseSubarray(array, 0, lengthOfTheFirstSubarray - 1);
    reverseSubarray(array, lengthOfTheFirstSubarray, lengthOfTheFirstSubarray + lengthOfTheSecondSubarray - 1);
    reverseSubarray(array, 0, lengthOfTheFirstSubarray + lengthOfTheSecondSubarray - 1);
}

#define arraySize 10000
int main()
{
    int lengthOfTheFirstSubarray = 0;
    int lengthOfTheSecondSubarray = 0;
    printf("Enter m (length of the first subarray):");
    scanf_s("%d", &lengthOfTheFirstSubarray);
    printf("Enter n (length of the second subarray):");
    scanf_s("%d", &lengthOfTheSecondSubarray);
    int array[arraySize] = { 0 };
    printf("Enter the array:\n");
    for (int i = 0; i < lengthOfTheFirstSubarray + lengthOfTheSecondSubarray; i++)
    {
        scanf_s("%d", &array[i]);
    }
    swapFirstNElementsAndLastMElements(array, lengthOfTheFirstSubarray, lengthOfTheSecondSubarray);
    printf("Array with swaped first m elements and last n elements:");
    for (int i = 0; i < lengthOfTheSecondSubarray + lengthOfTheFirstSubarray; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}