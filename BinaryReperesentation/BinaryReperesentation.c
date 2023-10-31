#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

#define NUMBER_SIZE sizeof(int) * 8
enum ERRORCODES
{
    ok,
    inputError,
};

const char* TEST_ERRORS[4] = { "ok", "sum fuction", "twos complement function", "to decimal function" };

bool isTwoArraysEqual(const char* const first, const char* const second, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (first[i] != second[i])
        {
            return false;
        }
    }
    return true;
}

void XOREverythingWithOnes(char* const binary, const size_t size)
{
    for (size_t i = size - 1; i + 1 >= 1; --i)
    {
        binary[i] ^= 1;
    }
}

int myMax(const int firstNumber, const int secondNumber)
{
    return firstNumber > secondNumber ? firstNumber : secondNumber;
}

void fromIntToBinary(int number, char* const binary)
{
    const bool sign = (number < 0);
    number = abs(number);
    for (size_t i = 0; i < NUMBER_SIZE; ++i)
    {
        binary[i] = 0;
    }
    for (size_t currentPosition = 1; number >= 1; ++currentPosition)
    {
        binary[NUMBER_SIZE - currentPosition] = (char)(number % 2) + 0;
        number >>= 1;
    }
    if (sign)
    {
        XOREverythingWithOnes(binary, NUMBER_SIZE);
        for (size_t i = NUMBER_SIZE - 1; i + 1 >= 1; ++i)
        {
            if (binary[i] == 0)
            {
                binary[i] = 1;
                break;
            }
            binary[i] = 0;
        }
    }
}

void getSum(const char* const firstNumber, const char* const secondNumber, char* const thirdNumber)
{
    size_t size = NUMBER_SIZE;
    bool transfered = false;
    for (size_t i = size - 1; i + 1 >= 1; --i)
    {
        char number = firstNumber[i] + secondNumber[i];
        if (transfered)
        {
            ++number;
            transfered = false;
        }
        if (number >= 2)
        {
            number = number % 2;
            transfered = true;
        }
        thirdNumber[i] = number;
    }
}

bool testCaseSum(int firstNumber, int secondNumber)
{
    char firstNumberBinary[NUMBER_SIZE] = "";
    fromIntToBinary(firstNumber, firstNumberBinary, NUMBER_SIZE);
    char secondNumberBinary[NUMBER_SIZE] = "";
    fromIntToBinary(secondNumber, secondNumberBinary, NUMBER_SIZE);
    char thirdNumberBinaryToCheck[NUMBER_SIZE] = "";
    char thirdNumberBinary[NUMBER_SIZE] = "";
    int thirdNumber = 0;
    fromIntToBinary(thirdNumber, thirdNumberBinary, NUMBER_SIZE);
    fromIntToBinary(firstNumber + secondNumber, thirdNumberBinaryToCheck, NUMBER_SIZE);
    getSum(firstNumberBinary, secondNumberBinary, thirdNumberBinary, NUMBER_SIZE);
    return isTwoArraysEqual(thirdNumberBinary, thirdNumberBinaryToCheck, NUMBER_SIZE);
}

int getSumTest(void)
{
    int firstNumber = 5;
    int secondNumber = -5;
    if (!testCaseSum(firstNumber, secondNumber))
    {
        return 1;
    }
    firstNumber = 6;
    secondNumber = 5;
    if (!testCaseSum(firstNumber, secondNumber))
    {
        return 2;
    }
    return ok;
}

int toDecimal(char* const binary)
{
    if (binary[0] == 1)
    {
        XOREverythingWithOnes(binary, NUMBER_SIZE);
        for (int i = NUMBER_SIZE - 1; i >= 1; --i)
        {
            if (binary[i] == 0)
            {
                binary[i] = 1;
                break;
            }
            binary[i] = 0;
        }
        binary[0] = 1;
    }

    int number = 0;
    size_t currentPosition = 1;
    for (size_t i = NUMBER_SIZE - 1; i >= 1; --i)
    {
        if (binary[i] == 1)
        {
            number += currentPosition;
        }
        currentPosition <<= 1;
    }
    if (binary[0] == 1) {
        number *= -1;
    }
    return number;
}

int toDecimalTest(void)
{
    const char number[NUMBER_SIZE] = "";
    int decimalNumber = -747;
    fromIntToBinary(decimalNumber, number);
    if (decimalNumber != toDecimal(number))
    {
        return 1;
    }
    const char secondNumber[NUMBER_SIZE] = "01011101011";
    decimalNumber = 747;
    fromIntToBinary(decimalNumber, secondNumber);
    if (decimalNumber != toDecimal(secondNumber))
    {
        return 2;
    }
    const char thirdNumber[NUMBER_SIZE] = "0101110110101011";
    decimalNumber = 23979;
    fromIntToBinary(decimalNumber, thirdNumber);
    if (decimalNumber != toDecimal(thirdNumber))
    {
        return 3;
    }   
    return ok;
}

bool testCaseFromIntToBinary(const int decimalNumber)
{
    char twosCompletmentNumber[NUMBER_SIZE] = "";
    fromIntToBinary(decimalNumber, twosCompletmentNumber);
    if (toDecimal(twosCompletmentNumber) != decimalNumber)
    {
        return false;
    }
    return true;
}

int fromIntToBinaryTest(void)
{
    int decimalNumber = -1;
    if (!testCaseFromIntToBinary(decimalNumber))
    {
        return 1;
    }
    decimalNumber = -7;
    if (!testCaseFromIntToBinary(decimalNumber))
    {
        return 2;
    }
    decimalNumber = 127;
    if (!testCaseFromIntToBinary(decimalNumber))
    {
        return 3;
    }
    return ok;
}

int tests(void)
{
    int result = getSumTest();
    if (result != ok)
    {
        return 10 + result;
    }
    result = fromIntToBinaryTest();
    if (result != ok)
    {
        return 20 + result;
    }
    result = toDecimalTest();
    if (result != ok)
    {
        return 30 + result;
    }
    return ok;
}

void printNumber(const char* const number, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%c", number[i] + '0');
    }
    printf("\n");
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    const int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN %s TEST, CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    int firstNumber = 0;
    printf("Введите первое число:");
    if (scanf_s("%d", &firstNumber) != 1)
    {
        printf("ОШИБКА ВВОДА\n");
        return inputError;
    }
    printf("Введите второе число:");
    char firstBinary[NUMBER_SIZE] = "";
    fromIntToBinary(firstNumber, firstBinary, NUMBER_SIZE);
    int secondNumber = 0;
    if (scanf_s("%d", &secondNumber) != 1)
    {
        printf("ОШИБКА ВВОДА\n");
        return inputError;
    };
    char secondBinary[NUMBER_SIZE] = { 0 };
    fromIntToBinary(secondNumber, secondBinary, NUMBER_SIZE);
    printf("Первое число в дополнительном коде:\n");
    printNumber(firstBinary, NUMBER_SIZE);
    printf("Второе число в дополнительном коде:\n");
    printNumber(secondBinary, NUMBER_SIZE);
    char thirdBinary[NUMBER_SIZE + 1] = { 0 };
    fromIntToBinary(0, thirdBinary, sizeof(int));
    getSum(firstBinary, secondBinary, thirdBinary, NUMBER_SIZE);
    printf("Сумма чисел в дополнительном коде:\n");
    printNumber(thirdBinary, NUMBER_SIZE);
    printf("\n");
    printf("Сумма чисел:");
    printf("%d\n", toDecimal(thirdBinary));
    return ok;
}
