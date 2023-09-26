#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void zFunction(char* string, int* zFunctionArray)
{
    int rightBorder = 0;
    int leftBorder = 0;
    int sizeOfString = strlen(string);
    for (int currentSymbol = 1; currentSymbol < sizeOfString; currentSymbol++)
    {
        if (currentSymbol <= rightBorder)
        {
            zFunctionArray[currentSymbol] = min(zFunctionArray[currentSymbol - leftBorder], rightBorder - currentSymbol + 1);
        }
        while (zFunctionArray[currentSymbol] + currentSymbol < sizeOfString && string[zFunctionArray[currentSymbol] + currentSymbol] == string[zFunctionArray[currentSymbol]])
        {
            zFunctionArray[currentSymbol]++;
        }
        if (currentSymbol + zFunctionArray[currentSymbol] - 1 > rightBorder)
        {
            rightBorder = currentSymbol + zFunctionArray[currentSymbol] - 1;
            leftBorder = currentSymbol;
        }
    }
}


int main()
{
    char string[1000] = "";
    char substring[1000] = "";
    printf("Enter the substring:");
    scanf_s("%s", substring, 1000);
    printf("Enter the string:");
    scanf_s("%s", string, 1000);
    char sumOfStrings[2100] = "";
    strncat_s(sumOfStrings, 2100, substring, 1000);
    strncat_s(sumOfStrings, 2100, "&", 1000);
    strncat_s(sumOfStrings, 2100, string, 1000);

    int zFunctionArray[2100] = { 0 };
    zFunction(sumOfStrings, zFunctionArray);
    int amountOfAccurances = 0;
    for (int i = 0; i < 2100; i++)
    {
        if (zFunctionArray[i] == strlen(substring))
        {
            amountOfAccurances++;
        }
    }
    printf("Amount of accurances of the substring in the string: %d", amountOfAccurances);
    return 0;
}