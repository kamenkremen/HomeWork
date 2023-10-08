#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

bool isTwoArraysEqual(int* first, int* second, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (first[i] != second[i])
        {
            return false;
        }
    }
    return true;
}

void XOREverythingWithOnes(int* binary, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        binary[i] = (binary[i] + 1) % 2;
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

void getTwosComplement(int number, int* binary, int size)
{
    int sign = 0;
    if (number < 0)
    {
        sign = 1;
    }
    int current = 1;
    number = abs(number);
    while (number >= 1)
    {
        binary[size - current] = number % 2;
        number /= 2;
        ++current;
    }
    if (sign)
    {
        if (sign)
        {
            XOREverythingWithOnes(binary, size);
            for (int i = size - 1; i >= 0; i--)
            {
                if (binary[i] == 0)
                {
                    binary[i] = 1;
                    return;
                }
                binary[i] = 0;
            }
        }
    }
}

void getSum(int* firstNumber, int* secondNumber, int* thirdNumber, int size)
{
    bool transfered = false;
    for (int i = size - 1; i >= 0; --i)
    {
        int number = firstNumber[i];
        if (i < size) {
            number += secondNumber[i];
        }
        if (transfered)
        {
            ++number;
            transfered = false;
        }
        if (number >= 2)
        {
            number %= 2;
            transfered = true;
        }
        thirdNumber[i] = number;
    }
}

int getSumTest(void)
{
    int firstNumber = 5;
    int secondNumber = -5;
    int firstNumberBinary[sizeof(int) * 8] = { 0 };
    getTwosComplement(firstNumber, firstNumberBinary, sizeof(int) * 8);
    int secondNumberBinary[sizeof(int) * 8] = { 0 };
    getTwosComplement(secondNumber, secondNumberBinary, sizeof(int) * 8);
    int thirdNumber = 0;
    int thirdNumberBinaryToCheck[sizeof(int) * 8] = { 0 };
    int thirdNumberBinary[sizeof(int) * 8] = { 0 };
    getSum(firstNumberBinary, secondNumberBinary, thirdNumberBinary, sizeof(int) * 8);
    if (!isTwoArraysEqual(thirdNumberBinary, thirdNumberBinaryToCheck, sizeof(int) * 8))
    {
        return 1;
    }
    firstNumber = 6;
    secondNumber = 5;
    for (int i = 0; i < sizeof(int) * 8; ++i)
    {
        firstNumberBinary[i] = 0;
        secondNumberBinary[i] = 0;
    }
    getTwosComplement(firstNumber, firstNumberBinary, sizeof(int) * 8); 
    getTwosComplement(secondNumber, secondNumberBinary, sizeof(int) * 8);
    thirdNumber = 11;
    getTwosComplement(11, thirdNumberBinaryToCheck, sizeof(int) * 8);
    getSum(firstNumberBinary, secondNumberBinary, thirdNumberBinary, sizeof(int) * 8);
    if (!isTwoArraysEqual(thirdNumberBinary, thirdNumberBinaryToCheck, sizeof(int) * 8))
    {
        return 2;
    }
    return 0;
}

int toDecimal(int* binary, int size)
{
    int number = 0;
    int current = 1;
    for (int i = size - 1; i > 0; --i)
    {
        if (binary[i] == 1)
        {
            number += current;
        }
        current *= 2;
    }
    if (binary[0] == 1) {
        number *= -1;
    }
    return number;
}

int toDecimalTest(void)
{
    int number[11] = {1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1};
    int decimalNumber = -747;
    if (decimalNumber != toDecimal(number, 11))
    {
        return 1;
    }
    int secondNumber[11] = { 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1 };
    decimalNumber = 747;
    if (decimalNumber != toDecimal(secondNumber, 11))
    {
        return 2;
    }
    int thirdNumber[16] = { 0, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1 };
    decimalNumber = 23979;
    if (decimalNumber != toDecimal(thirdNumber, 16))
    {
        return 3;
    }
    return 0;
}

int getTwosComplementTest(void)
{
    int decimalNumber = -1;
    int twosCompletmentNumber[sizeof(int) * 8] = { 0 };
    int twosCompletmentNumberForCheck[sizeof(int) * 8] = { 0 };
    for (int i = 0; i < sizeof(int) * 8; i++)
    {
        twosCompletmentNumberForCheck[i] = 1;
    }
    getTwosComplement(decimalNumber, twosCompletmentNumber, sizeof(int) * 8);
    if (!isTwoArraysEqual(twosCompletmentNumberForCheck, twosCompletmentNumber, sizeof(int) * 8))
    {
        return 1;
    }
    decimalNumber = -7;
    int secondTwosCompletmentNumber[sizeof(int) * 8] = { 0 };
    int secondTwosCompletmentNumberForCheck[sizeof(int) * 8] = { 0 };
    for (int i = 0; i < sizeof(int) * 8; i++)
    {
        secondTwosCompletmentNumberForCheck[i] = 1;
    }
    secondTwosCompletmentNumberForCheck[sizeof(int) * 8 - 2] = 0;
    secondTwosCompletmentNumberForCheck[sizeof(int) * 8 - 3] = 0;
    getTwosComplement(decimalNumber, secondTwosCompletmentNumber, sizeof(int) * 8);
    if (!isTwoArraysEqual(secondTwosCompletmentNumber, secondTwosCompletmentNumberForCheck, sizeof(int) * 8))
    {
        return 2;
    }
    decimalNumber = 127;
    int thirdTwosCompletmentNumber[sizeof(int) * 8] = { 0 };
    int thirdTwosCompletmentNumberForCheck[sizeof(int) * 8] = { 0 };
    for (int i = 1; i < 8; i++)
    {
        thirdTwosCompletmentNumberForCheck[sizeof(int) * 8 - i] = 1;
    }
    getTwosComplement(decimalNumber, thirdTwosCompletmentNumber, sizeof(int) * 8);
    if (!isTwoArraysEqual(thirdTwosCompletmentNumber, thirdTwosCompletmentNumberForCheck, sizeof(int) * 8))
    {
        return 3;
    }
    return 0;
}

int tests(void)
{
    if (getSumTest() != 0)
    {
        return 10 + getSumTest();
    }
    if (getTwosComplementTest() != 0)
    {
        return 20 + getTwosComplementTest();
    }
    if (toDecimalTest() != 0)
    {
        return 30 + toDecimalTest();
    }
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ERROR %d\n", errorCode);
        return errorCode;
    }
    int firstNumber = 0;
    printf("Введите первое число:");
    if (scanf_s("%d", &firstNumber) != 1)
    {
        printf("ОШИБКА ВВОДА");
        return 1;
    }
    printf("Введите второе число:");
    int firstBinary[sizeof(int) * 8] = { 0 };
    getTwosComplement(firstNumber, firstBinary, sizeof(int) * 8);
    int secondNumber = 0;
    if (scanf_s("%d", &secondNumber) != 1)
    {
        printf("ОШИБКА ВВОДА");
        return 1;
    };
    int secondBinary[sizeof(int) * 8] = { 0 };
    getTwosComplement(secondNumber, secondBinary, sizeof(int) * 8);
    printf("Первое число в дополнительном коде:");
    for (int i = 0; i < sizeof(int) * 8; i++)
    {
        printf("%d", firstBinary[i]);
    }
    printf("\n");
    printf("Второе число в дополнительном коде:");
    for (int i = 0; i < sizeof(int) * 8; ++i)
    {
        printf("%d", secondBinary[i]);
    }
    int thirdBinary[sizeof(int) * 8] = { 0 };
    getSum(firstBinary, secondBinary, thirdBinary, sizeof(int) * 8);
    printf("\n");
    printf("Сумма чисел в дополнительном коде:");
    for (int i = 0; i < sizeof(int) * 8; i++)
    {
        printf("%d", thirdBinary[i]);
    }
    printf("\n");
    if (thirdBinary[0] == 1)
    {
        XOREverythingWithOnes(thirdBinary, sizeof(int) * 8);
        for (int i = sizeof(int) * 8 - 1; i >= 0; i--)
        {
            if (thirdBinary[i] == 0)
            {
                thirdBinary[i] = 1;
                break;
            }
            thirdBinary[i] = 0;
        }
        thirdBinary[0] = 1;
    }
    printf("\n");
    printf("Сумма чисел:");
    printf("%d", toDecimal(thirdBinary, sizeof(int) * 8));
    return 0;
}