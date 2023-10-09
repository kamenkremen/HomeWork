#include "sortings.h"

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