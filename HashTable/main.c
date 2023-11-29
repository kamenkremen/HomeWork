#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HashTable.h"
#include "List.h"
#include "ErrorCodes.h"
#include "Strings.h"
#include "Tests.h"

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    char* string = read("input.txt");
    if (string == NULL)
    {
        printf("MEMORY ERROR\n");
        return memoryError;
    }
    Table* table = createTable();
    if (table == NULL)
    {
        printf("MEMORY ERROR\n");
        free(string);
        return memoryError;
    }
    errorCode = addWordsToTable(table, string);
    free(string);
    if (errorCode != ok)
    {
        printf("MEMORY ERROR\n");
        deleteTable(&table);
        return memoryError;
    }
    printTable(table);
    printf("Average list length - %f\n", averageListLength(table, &errorCode));
    printf("Maximum list length - %u\n", maxListLength(table, &errorCode));
    printf("Load factor - %f\n", loadFactor(table, &errorCode));
    deleteTable(&table);
    return ok;
}
