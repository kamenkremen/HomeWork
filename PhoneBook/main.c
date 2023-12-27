#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <malloc.h>

#include "Files.h"
#include "ErrorCodes.h"
#include "Strings.h"
#include "Tests.h"
#include "PhoneBook.h"

#define COMMANDS "Enter 0 to exit\n\
Enter 1 to add new recording\n\
Enter 2 to print recordings\n\
Enter 3 to find phone by name\n\
Enter 4 to find name by phone\n\
Enter 5 to save current data\n"
#define PHONE_BOOK "phoneBook.txt"
#define MAX_SIZE 100
#define FAILED_TESTS 1

// телефонная кнгиа хранится в виде номер имя, где отдельная запись находится на отдельной строrе

enum Operations
{
    exitOperation,
    addOperation,
    printOperaion,
    findPhoneOperation,
    findNameOperation,
    saveDataOperation,
};

static bool addToBook(char** const numbers, char** const names, const size_t size, size_t* const newRecordings)
{
    if (size + *newRecordings >= 100)
    {
        printf("MAX AMOUNT OF RECORDINGS ACHIEVED\n");
        return false;
    }
    free(readLine());
    printf("Enter number:\n");
    const char* const number = readLine();
    if (number == NULL)
    {
        freeData(numbers, names, *newRecordings + size);
        return true;
    }
    if (number == "")
    {
        printf("Number can`t be a blank space\n");
        free(number);
        return false;
    }
    printf("Enter name:\n");
    const char* const name = readLine();
    if (name == NULL)
    {
        freeData(numbers, names, *newRecordings + size);
        free(number);
        return true;
    }
    names[size + *newRecordings] = name;
    numbers[size + *newRecordings] = number;
    ++*newRecordings;
    return false;
}

static bool find(char** const searchWhere, char** const searchWhat, const size_t size, const size_t newRecordings, const bool lookingForNumbers)
{
    free(readLine());
    printf("Enter %s:\n", lookingForNumbers ? "name" : "number");
    const char* const string = readLine();
    if (string == NULL)
    {
        printf("INPUT ERROR\n");
        freeData(searchWhere, searchWhat, newRecordings + size);
        return true;
    }
    printf("%ss:\n", !lookingForNumbers ? "name" : "number");
    for (size_t i = 0; i < size + newRecordings; ++i)
    {
        if (strcmp(searchWhere[i], string) == 0)
        {
            printf("%s\n", searchWhat[i]);
        }
    }
    free(string);
    return false;
}

int main(void)
{
    if (tests())
    {
        return FAILED_TESTS;
    }
    char* numbers[MAX_SIZE] = { 0 };
    char* names[MAX_SIZE] = { 0 };
    size_t size = 0;
    readBook(numbers, names, &size, PHONE_BOOK);
    size_t newRecordings = 0;
    while (true)
    {
        printf(COMMANDS);
        int comand = 0;
        if (scanf_s("%d", &comand) != 1)
        {
            printf("INPUT ERROR\n");
            freeData(numbers, names, newRecordings + size);
            return inputError;
        }
        switch (comand)
        {
        case exitOperation:
            freeData(numbers, names, newRecordings + size);
            return ok;
        case addOperation:
            if (addToBook(numbers, names, size, &newRecordings))
            {
                printf("INPUT ERROR\n");
                return inputError;
            }
            break;
        case printOperaion:
            for (size_t i = 0; i < size + newRecordings; ++i)
            {
                printf("Number: %s, name: %s\n", numbers[i], names[i]);
            }
            break;
        case findPhoneOperation:
            if (find(names, numbers, size, newRecordings, true))
            {
                return inputError;
            }
            break;
        case findNameOperation:
            if (find(numbers, names, size, newRecordings, false))
            {
                return inputError;
            }
            break;
        case saveDataOperation:
            if (writeBook(numbers, names, &size, PHONE_BOOK, &newRecordings))
            {
                printf("ERROR IN WRITING IN THE FILE\n");
            }
            else
            {
                printf("Succesfully saved\n");
            }
            break;
        default:
            printf("Enter the number between 0 and 9\n");
        }
    }
    return ok;
}
