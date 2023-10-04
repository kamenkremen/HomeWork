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

bool isPalindromeTest(void)
{
    char* stringTest = "nePalindrom";
    if (isPalindrome(stringTest))
    {
        return true;
    } 
    stringTest = "aBobA";
    if (isPalindrome(stringTest))
    {
        return true;
    }
    stringTest = "abOba";
    if (!isPalindrome(stringTest))
    {
        return true;
    }
    stringTest = "a b    o b       a";
    if (!isPalindrome(stringTest))
    {
        return true;
    }
    return false;
}

int tests(void)
{
    if (isPalindromeTest())
    {
        return 1;
    }
    return 0;
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