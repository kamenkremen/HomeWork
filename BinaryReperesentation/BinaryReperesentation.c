#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

enum ERRORCODES
{
    ok,
    inputError,
};
const char* TEST_ERRORS[4] = { "ok", "sum fuction", "twos complement function", "to decimal function" };

bool isTwoArraysEqual(const char* const first, const char* const second, const size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        if (first[i] != second[i])
        {
            printf("%c, %c\n", first[i], second[i]);
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

void getTwosComplement(int number, char* const binary, const size_t size)
{
    const int sign = number < 0 ? 1 : 0;
   // printf("%d, %d\n", number, sign);
    int current = 1;
    number = abs(number);
    for (size_t i = 0; i < size; ++i)
    {
        binary[i] = '0';
    }
    while (number >= 1)
    {
        binary[size - current] = (char)(number % 2) + '0';
        number /= 2;
        ++current;
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

void getSum(const char* const firstNumber, const char* const secondNumber, char* const thirdNumber, const size_t size)
{
    bool transfered = false;
    for (size_t i = size - 1; i != -1; --i)
    {
        int number = firstNumber[i] - '0';
        
        if (i < size) {
            number += secondNumber[i] - '0';
        }
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
}

int getSumTest(void)
{
    int firstNumber = 5;
    int secondNumber = -5;
    char firstNumberBinary[sizeof(int) * 8 + 1] = "";
    getTwosComplement(firstNumber, firstNumberBinary, sizeof(int) * 8);
    char secondNumberBinary[sizeof(int) * 8 + 1] = "";
    getTwosComplement(secondNumber, secondNumberBinary, sizeof(int) * 8);
    int thirdNumber = 0;
    char thirdNumberBinaryToCheck[sizeof(int) * 8 + 1] = "";
    char thirdNumberBinary[sizeof(int) * 8 + 1] = "";
    getTwosComplement(thirdNumber, thirdNumberBinary, sizeof(int) * 8);
    getTwosComplement(thirdNumber, thirdNumberBinaryToCheck, sizeof(int) * 8);
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
    getTwosComplement(0, thirdNumberBinary, sizeof(int) * 8);
    getSum(firstNumberBinary, secondNumberBinary, thirdNumberBinary, sizeof(int) * 8);
    printf("%s, %s\n", thirdNumberBinary, thirdNumberBinaryToCheck);
    if (!isTwoArraysEqual(thirdNumberBinary, thirdNumberBinaryToCheck, sizeof(int) * 8))
    {
        return 2;
    }
    return ok;
}

int toDecimal(const char* const binary, const size_t size)
{
    int number = 0;
    int current = 1;
    for (size_t i = size - 1; i > 0; --i)
    {
        if (binary[i] == '1')
        {
            number += current;
        }
        current *= 2;
    }
    if (binary[0] == '1') {
        number *= -1;
    }
    return number;
}

int toDecimalTest(void)
{
    const char number[11] = "11011101011";
    int decimalNumber = -747;
    if (decimalNumber != toDecimal(number, 11))
    {
        return 1;
    }
    const char secondNumber[11] = "01011101011";
    decimalNumber = 747;
    if (decimalNumber != toDecimal(secondNumber, 11))
    {
        return 2;
    }
    const char thirdNumber[16] = "0101110110101011";
    decimalNumber = 23979;
    if (decimalNumber != toDecimal(thirdNumber, 16))
    {
        return 3;
    }
    return ok;
}

int getTwosComplementTest(void)
{
    int decimalNumber = -1;
    char twosCompletmentNumber[sizeof(int) * 8 + 1] = { 0 };
    const char twosCompletmentNumberForCheck[sizeof(int) * 8 + 1] = "11111111111111111111111111111111";
    getTwosComplement(decimalNumber, twosCompletmentNumber, sizeof(int) * 8);
    if (!isTwoArraysEqual(twosCompletmentNumberForCheck, twosCompletmentNumber, sizeof(int) * 8))
    {
        return 1;
    }
    decimalNumber = -7;
    char secondTwosCompletmentNumber[sizeof(int) * 8 + 1] = { 0 };
    const char secondTwosCompletmentNumberForCheck[sizeof(int) * 8 + 1] = "11111111111111111111111111111001";
    getTwosComplement(decimalNumber, secondTwosCompletmentNumber, sizeof(int) * 8);
    if (!isTwoArraysEqual(secondTwosCompletmentNumber, secondTwosCompletmentNumberForCheck, sizeof(int) * 8))
    {
        return 2;
    }
    decimalNumber = 127;
    char thirdTwosCompletmentNumber[sizeof(int) * 8 + 1] = { 0 };
    const char thirdTwosCompletmentNumberForCheck[sizeof(int) * 8 + 1] = "00000000000000000000000001111111";
    getTwosComplement(decimalNumber, thirdTwosCompletmentNumber, sizeof(int) * 8);
    if (!isTwoArraysEqual(thirdTwosCompletmentNumber, thirdTwosCompletmentNumberForCheck, sizeof(int) * 8))
    {
        return 3;
    }
    return ok;
}

int tests(void)
{
    if (getSumTest() != ok)
    {
        return 10 + getSumTest();
    }
    if (getTwosComplementTest() != ok)
    {
        return 20 + getTwosComplementTest();
    }
    if (toDecimalTest() != ok)
    {
        return 30 + toDecimalTest();
    }
    return ok;
}

int main(void)
{
    setlocale(LC_ALL, "Russian");
    const int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN %s FUNCTION, CASE %d\n", TEST_ERRORS[errorCode / 10], errorCode % 10);
        return errorCode;
    }
    int firstNumber = 0;
    printf("Введите первое число:");
    if (scanf_s("%d", &firstNumber) != 1)
    {
        printf("ОШИБКА ВВОДА");
        return inputError;
    }
    printf("Введите второе число:");
    char firstBinary[sizeof(int) * 8 + 1] = "";
    getTwosComplement(firstNumber, firstBinary, sizeof(int) * 8);
    int secondNumber = 0;
    if (scanf_s("%d", &secondNumber) != 1)
    {
        printf("ОШИБКА ВВОДА");
        return inputError;
    };
    char secondBinary[sizeof(int) * 8 + 1] = { 0 };
    getTwosComplement(secondNumber, secondBinary, sizeof(int) * 8);
    printf("Первое число в дополнительном коде: %s\n", firstBinary);
    printf("Второе число в дополнительном коде: %s\n", secondBinary);
    char thirdBinary[sizeof(int) * 8 + 1] = { 0 };
    getTwosComplement(0, thirdBinary, sizeof(int));
    getSum(firstBinary, secondBinary, thirdBinary, sizeof(int) * 8);
    printf("Сумма чисел в дополнительном коде: %s\n", thirdBinary);
    if (thirdBinary[0] == '1')
    {
        XOREverythingWithOnes(thirdBinary, sizeof(int) * 8);
        for (int i = sizeof(int) * 8 - 1; i >= 0; --i)
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
    printf("%d\n", toDecimal(thirdBinary, sizeof(int) * 8));
    return ok;
}
