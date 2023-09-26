#include <stdio.h>

int findIncompleteQuotient(int divident, int divider)
{
    int quotient = 0;
    const int signDeterminant = divident * divider;
    int sign = 1;
    if (signDeterminant < 0)
    {
        sign = -1;
    }
    while (divident < 0 || divident >= abs(divider))
    {
        divident -= sign * divider;
        quotient++;
    }
    if (signDeterminant < 0)
    {
        quotient *= -1;
    }
    return quotient;
}

int main()
{
    int divident = 0;
    int divider = 0;
    printf("Enter divident: ");
    scanf_s("%d", &divident);
    printf("Enter divider: ");
    scanf_s("%d", &divider);
    if (divider == 0)
    {
        printf("Divider must be non-zero.");
        return 0;
    }
    int quotient = findIncompleteQuotient(divident, divider);
    printf("Incomplete quotient:%d", quotient);
    return 0;
}