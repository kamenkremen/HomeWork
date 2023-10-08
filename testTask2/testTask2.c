#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

void bubbleSortButOnlyEven(int* array, const int size)
{
    for (int i = 0; i < size; i += 2)
    {
        for (int j = 0; j < size - 2 - i; j += 2)
        {
            if (array[j] > array[j + 2])
            {
                int numberForSwap = array[j];
                array[j] = array[j + 2];
                array[j + 2] = numberForSwap;
            }
        }
    }
}

bool isArraysEqual(int* array1, int* array2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

int testForBubbleSort(void)
{
    int testArray[10] = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
    int sortedArray[10] = { 1, 2, 2, 4, 3, 5, 4, 3, 5, 1 };
    bubbleSortButOnlyEven(testArray, 10);
    if (!isArraysEqual(testArray, sortedArray, 10))
    {
        return 1;
    }
    int testArray2[5] = { 5, 4, 3, 2, 1 };
    int sortedArray2[5] = { 1, 4, 3, 2, 5 };
    bubbleSortButOnlyEven(testArray2, 5);
    if (!isArraysEqual(testArray2, sortedArray2, 5))
    {
        return 2;
    }
    int testArray3[10] = { 1, 5, 2, 7, 3, 1, 4, 12, 5, 3 };
    int sortedArray3[10] = { 1, 5, 2, 7, 3, 1, 4, 12, 5, 3 };
    bubbleSortButOnlyEven(testArray3, 10);
    if (!isArraysEqual(testArray3, sortedArray3, 10))
    {
        return 3;
    }
    return 0;
}

int tests(void)
{
    return testForBubbleSort();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ОШИБКА %d\n", errorCode);
        return errorCode;
    }
    printf("Введите длину массива:");
    int size = 0;
    if (scanf_s("%d", &size) != 1)
    {
        printf("ОШИБКА ВВОДА");
        return 1;
    }
    int* array = calloc(size, sizeof(int));
    if (array == NULL)
    {
        printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ");
        return 2;
    }
    printf("Введите элементы массива:");
    for (int i = 0; i < size; i++) 
    {
        int x = 0;
        if (scanf_s("%d", &x) != 1)
        {
            printf("ОШИБКА ВВОДА");
            free(array);
            return 1;
        }
        array[i] = x;
    }
    bubbleSortButOnlyEven(array, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    return 0;
}