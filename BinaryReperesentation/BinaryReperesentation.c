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
    for (size_t i = size - 1; i != -1; --i)
    {
        binary[i] = '0' + ((binary[i] - '0') + 1) % 2;
    }
}

int myMax(const int firstNumber, const int secondNumber)
{
    return firstNumber > secondNumber ? firstNumber : secondNumber;
}

void fromIntToBinary(int number, char* const binary, const size_t size)
{
    const bool sign = (number < 0);
    number = abs(number);
    for (size_t i = 0; i < size; ++i)
    {
        binary[i] = '0';
    }
    for (size_t currentPosition = 1; number >= 1; ++currentPosition)
    {
        binary[size - currentPosition] = (char)(number % 2) + '0';
        number >>= 1;
    }
    if (sign)
    {
        XOREverythingWithOnes(binary, size);
        for (size_t i = size - 1; i != 0; --i)
        {
            if (binary[i] == '0')
            {
                binary[i] = '1';
                binary[size] = '\0';
                return;
            }
            binary[i] = '0';
        }
    }
    binary[size] = '\0';
}

void getSum(const char* const firstNumber, const char* const secondNumber, char* const thirdNumber)
{
    size_t size = strlen(firstNumber);
    bool transfered = false;
    for (size_t i = size - 1; i != -1; --i)
    {
        int number = firstNumber[i] - '0' + secondNumber[i] - '0';
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
        thirdNumber[i] = number + '0';
    }
    thirdNumber[size] = '\0';
}

int getSumTest(void)
{
    int firstNumber = 5;
    int secondNumber = -5;
    char firstNumberBinary[NUMBER_SIZE + 1] = "";
    fromIntToBinary(firstNumber, firstNumberBinary, NUMBER_SIZE);
    char secondNumberBinary[NUMBER_SIZE + 1] = "";
    fromIntToBinary(secondNumber, secondNumberBinary, NUMBER_SIZE);
    char thirdNumberBinaryToCheck[NUMBER_SIZE + 1] = "";
    char thirdNumberBinary[NUMBER_SIZE + 1] = "";
    fromIntToBinary(0, thirdNumberBinary, NUMBER_SIZE);
    fromIntToBinary(firstNumber + secondNumber, thirdNumberBinaryToCheck, NUMBER_SIZE);
    getSum(firstNumberBinary, secondNumberBinary, thirdNumberBinary, NUMBER_SIZE);
    if (!isTwoArraysEqual(thirdNumberBinary, thirdNumberBinaryToCheck, NUMBER_SIZE))
    {
        return 1;
    }
    firstNumber = 6;
    secondNumber = 5;
    for (size_t i = 0; i < NUMBER_SIZE; ++i)
    {
        firstNumberBinary[i] = 0;
        secondNumberBinary[i] = 0;
    }
    fromIntToBinary(firstNumber, firstNumberBinary, NUMBER_SIZE); 
    fromIntToBinary(secondNumber, secondNumberBinary, NUMBER_SIZE);
    fromIntToBinary(firstNumber + secondNumber, thirdNumberBinaryToCheck, NUMBER_SIZE);
    fromIntToBinary(0, thirdNumberBinary, NUMBER_SIZE);
    getSum(firstNumberBinary, secondNumberBinary, thirdNumberBinary, NUMBER_SIZE);
    if (!isTwoArraysEqual(thirdNumberBinary, thirdNumberBinaryToCheck, NUMBER_SIZE))
    {
        return 2;
    }
    return ok;
}

int toDecimal(const char* const binary)
{
    int number = 0;
    size_t currentPosition = 1;
    size_t size = strlen(binary);
    for (size_t i = size - 1; i > 0; --i)
    {
        if (binary[i] == '1')
        {
            number += currentPosition;
        }
        currentPosition <<= 1;
    }
    if (binary[0] == '1') {
        number *= -1;
    }
    return number;
}

int toDecimalTest(void)
{
    const char number[12] = "11011101011";
    int decimalNumber = -747;
    if (decimalNumber != toDecimal(number))
    {
        return 1;
    }
    const char secondNumber[12] = "01011101011";
    decimalNumber = 747;
    if (decimalNumber != toDecimal(secondNumber))
    {
        return 2;
    }
    const char thirdNumber[18] = "0101110110101011";
    decimalNumber = 23979;
    if (decimalNumber != toDecimal(thirdNumber))
    {
        return 3;
    }   
    return ok;
}

int fromIntToBinaryTest(void)
{
    int decimalNumber = -1;
    char twosCompletmentNumber[NUMBER_SIZE + 1] = { 0 };
    const char twosCompletmentNumberForCheck[NUMBER_SIZE + 1] = "11111111111111111111111111111111";
    fromIntToBinary(decimalNumber, twosCompletmentNumber, NUMBER_SIZE);
    if (!isTwoArraysEqual(twosCompletmentNumberForCheck, twosCompletmentNumber, NUMBER_SIZE))
    {
        return 1;
    }
    decimalNumber = -7;
    char secondTwosCompletmentNumber[NUMBER_SIZE + 1] = { 0 };
    const char secondTwosCompletmentNumberForCheck[NUMBER_SIZE + 1] = "11111111111111111111111111111001";
    fromIntToBinary(decimalNumber, secondTwosCompletmentNumber, NUMBER_SIZE);
    if (!isTwoArraysEqual(secondTwosCompletmentNumber, secondTwosCompletmentNumberForCheck, NUMBER_SIZE))
    {
        return 2;
    }
    decimalNumber = 127;
    char thirdTwosCompletmentNumber[NUMBER_SIZE + 1] = { 0 };
    const char thirdTwosCompletmentNumberForCheck[NUMBER_SIZE + 1] = "00000000000000000000000001111111";
    fromIntToBinary(decimalNumber, thirdTwosCompletmentNumber, NUMBER_SIZE);
    if (!isTwoArraysEqual(thirdTwosCompletmentNumber, thirdTwosCompletmentNumberForCheck, NUMBER_SIZE))
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
    char firstBinary[NUMBER_SIZE + 1] = "";
    fromIntToBinary(firstNumber, firstBinary, NUMBER_SIZE);
    int secondNumber = 0;
    if (scanf_s("%d", &secondNumber) != 1)
    {
        printf("ОШИБКА ВВОДА\n");
        return inputError;
    };
    char secondBinary[NUMBER_SIZE + 1] = { 0 };
    fromIntToBinary(secondNumber, secondBinary, NUMBER_SIZE);
    printf("Первое число в дополнительном коде: %s\n", firstBinary);
    printf("Второе число в дополнительном коде: %s\n", secondBinary);
    char thirdBinary[NUMBER_SIZE + 1] = { 0 };
    fromIntToBinary(0, thirdBinary, sizeof(int));
    getSum(firstBinary, secondBinary, thirdBinary, NUMBER_SIZE);
    printf("Сумма чисел в дополнительном коде: %s\n", thirdBinary);
    if (thirdBinary[0] == '1')
    {
        XOREverythingWithOnes(thirdBinary, NUMBER_SIZE);
        for (int i = NUMBER_SIZE - 1; i >= 0; --i)
        {
            if (thirdBinary[i] == '0')
            {
                thirdBinary[i] = '1';
                break;
            }
            thirdBinary[i] = '0';
        }
        thirdBinary[0] = '1';
    }
    printf("\n");
    printf("Сумма чисел:");
    printf("%d\n", toDecimal(thirdBinary));
    return ok;
}
