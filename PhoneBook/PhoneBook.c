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

#define COMMANDS "Enter 0 to exit\n\
Enter 1 to add new recording\n\
Enter 2 to print recordings\n\
Enter 3 to find phone by name\n\
Enter 4 to find name by phone\n\
Enter 5 to save current data\n"
#define PHONE_BOOK "phoneBook.txt"
#define MAX_SIZE 100
#define FAILED_TESTS 1

enum Operations
{
    exitOperation,
    addOperation,
    printOperaion,
    findPhoneOperation,
    findNameOperation,
    saveDataOperation,
};

static void freeData(char** const numbers, char** const names, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(numbers[i]);
        free(names[i]);
    }
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
    char* number = "";
    char* name = "";
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
            readLine();
            printf("Enter number:\n");
            number = readLine();
            if (number == NULL)
            {
                freeData(numbers, names, newRecordings + size);
                return inputError;
            }
            if (number == "")
            {
                printf("Number can`t be a blank space\n");
                free(number);
                break;
            }
            printf("Enter name:\n");
            name = readLine();
            if (name == NULL)
            {
                freeData(numbers, names, newRecordings + size);
                free(number);
                return inputError;
            }
            names[size + newRecordings] = name;
            numbers[size + newRecordings] = number;
            ++newRecordings;
            break;
        case printOperaion:
            for (size_t i = 0; i < size + newRecordings; ++i)
            {
                printf("Number: %s, name: %s\n", numbers[i], names[i]);
            }
            break;
        case findPhoneOperation:
            readLine();
            printf("Enter name:\n");
            name = readLine();
            if (name == NULL)
            {
                printf("INPUT ERROR\n");
                freeData(numbers, names, newRecordings + size);
                return inputError;
            }
            for (size_t i = 0; i < size + newRecordings; ++i)
            {
                if (strcmp(names[i], name) == 0)
                {
                    printf("%s\n", numbers[i]);
                }
            }
            free(name);
            break;
        case findNameOperation:
            readLine();
            printf("Enter phone:\n");
            number = readLine();
            if (number == NULL)
            {
                printf("INPUT ERROR\n");
                freeData(numbers, names, newRecordings + size);
                return inputError;
            }
            for (size_t i = 0; i < size + newRecordings; ++i)
            {
                if (strcmp(numbers[i], number) == 0)
                {
                    printf("%s\n", names[i]);
                }
            }
            free(number);
            break;
        case saveDataOperation:
            if (writeBook(numbers, names, &size, PHONE_BOOK, &newRecordings))
            {
                printf("ERROR IN WRITING IN THE FILE\n");
            }
            break;
        default:
            printf("Enter the number between 0 and 9\n");
        }
    }
    return ok;
}
