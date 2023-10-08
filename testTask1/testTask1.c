#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

#define mainString "я иду с мечем судия"

int isPalindrome(char* string)
{
    int length = strlen(string);
    int i = 0;
    int j = length - 1;
    while (i < j)
    {
        while (string[i] == ' ')
        {
            ++i;
        }
        while (string[j] == ' ')
        {
            --j;
        }
        if (string[i] != string[j])
        {
            return 0;
        }
        ++i;
        --j;
    }
    return 1;
}

int isPalindromeTest(void)
{
    char* stringTest = "nePalindrom";
    if (isPalindrome(stringTest))
    {
        return 1;
    } 
    stringTest = "aBobA";
    if (isPalindrome(stringTest))
    {
        return 2;
    }
    stringTest = "abOba";
    if (!isPalindrome(stringTest))
    {
        return 3;
    }
    stringTest = "a b    o b       a";
    if (!isPalindrome(stringTest))
    {
        return 4;
    }
    return 0;
}

int tests(void)
{
    return isPalindromeTest();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ОШИБКА %d\n", errorCode);
        return errorCode;
    }
    if (isPalindrome(mainString))
    {
        printf("%s is palindrome.",mainString);
    }
    else
    {
        printf("%s is not a palindrome.", mainString);
    }
    return 0;
}