#include <stdio.h>

int main()
{
    int firstNumber = 0;
    int secondNumber = 0;
    printf("First number:");
    scanf_s("%d", &firstNumber);
    printf("Second number:");
    scanf_s("%d", &secondNumber);
    firstNumber += secondNumber;
    secondNumber -= firstNumber;
    firstNumber += secondNumber;
    secondNumber *= -1;
    printf("First number:%d, second number:%d", firstNumber, secondNumber);
    return 0;
}
