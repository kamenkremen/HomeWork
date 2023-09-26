#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    char braces[1000] = "";
    printf("Enter string:");
    scanf_s("%s", braces, 1000);
    int balanceOfBraces = 0;
    bool stringBalanced = true;
    for (int i = 0; i < strlen(braces); i++)
    {
        if (braces[i] == '(')
        {
            balanceOfBraces++;
        }
        if (braces[i] == ')')
        {
            balanceOfBraces--;
        }
        if (balanceOfBraces < 0)
        {
            stringBalanced = false;
            break;
        }
    }
    if (balanceOfBraces != 0)
    {
        stringBalanced = false;
    }
    if (stringBalanced)
    {
        printf("String is balanced");
    }
    else
    {
        printf("String is not balanced");
    }
    return 0;
}