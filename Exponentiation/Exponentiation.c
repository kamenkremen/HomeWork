#include <stdio.h>
#include <stdlib.h>

int linearExponentiation(const int number, const int power) {
    int result = 1;
    for (int currentPower = 0; currentPower < power; currentPower++)
    {
        result *= number;
    }
    return result;
}

int binaryExponentiation(const int number, const int power)
{
    if (power == 0)
    {
        return 1;
    }
    if (power % 2 == 1)
    {
        return number * (binaryExponentiation(number, power - 1));
    }
    int transitionalNumber = binaryExponentiation(number, power / 2);
    return transitionalNumber * transitionalNumber;
}

int main()
{
    printf("Enter the number:");
    int number = 0;
    scanf_s("%d", &number);
    printf("Enter the power:");
    int power = 0;
    scanf_s("%d", &power);
    int finalNumber = binaryExponentiation(number, power);
    printf("%d ^ %d = %d", number, power, finalNumber);
    return 0;
}