#include <stdio.h>
int main() {
    int userArraySize = 0;
    printf("Array size:");
    scanf_s("%d", &userArraySize);
    while (userArraySize <= 0)
    {
        printf("Incorrect size. Enter correct one:");
        scanf_s("%d", &userArraySize);
    }
    int countOfZeros = 0;
    for (int i = 0; i < userArraySize; i++)
    {
        int num = 0;
        printf("%d st number of array:", i + 1);
        scanf_s("%d", &num);
        if (num == 0)
        {
            countOfZeros++;
        }
    }
    printf("Number of zeros = %d", countOfZeros);

    return 0;
}