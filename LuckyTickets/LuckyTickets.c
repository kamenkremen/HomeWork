#include <stdio.h>

int main()
{
    int quantityOfNumbersWithCertainSum[28] = { 0 };
    for (int firstDigit = 0; firstDigit <= 9; firstDigit++)
    {
        for (int secondDigit = 0; secondDigit <= 9; secondDigit++)
        {
            for (int thirdDigit = 0; thirdDigit <= 9; thirdDigit++)
            {
                quantityOfNumbersWithCertainSum[firstDigit + secondDigit + thirdDigit]++;
            }
        }
    }
    int amountOfLuckyTickets = 0;
    for (int i = 0; i < 28; i++)
    {
        amountOfLuckyTickets += quantityOfNumbersWithCertainSum[i] * quantityOfNumbersWithCertainSum[i];
    }
    printf("Amount of lucky tickets:%d", amountOfLuckyTickets);
    return 0;
}