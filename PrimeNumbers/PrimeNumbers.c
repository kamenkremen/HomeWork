#include <stdio.h>
#include <stdbool.h>

#define ERATOSTHENESSIEVESIZE 10000
void fillSieve(bool* eratosthenesSieve, int number)
{
    for (int i = 0; i < ERATOSTHENESSIEVESIZE; i++)
    {
        eratosthenesSieve[i] = true;
    }
    for (int i = 2; i < number; i++)
    {
        if (!eratosthenesSieve[i])
        {
            continue;
        }
        for (int j = i * i; j < number; j += i)
        {
            if (j > number || j > ERATOSTHENESSIEVESIZE)
            {
                break;
            }
            eratosthenesSieve[j] = false;
        }
    }
}

int main()
{
    bool eratosthenesSieve[ERATOSTHENESSIEVESIZE] = { true };
    printf("Enter the number: ");
    int number = 0;
    scanf_s("%d", &number);
    fillSieve(eratosthenesSieve, number);
    printf("Prime numbers <= %d: ", number);
    for (int i = 2; i < number; i++)
    {
        if (eratosthenesSieve[i])
        {
            printf("%d ", i);
        }
    }
    return 0;
}