#include <stdlib.h>

#include "Tests.h"
#include "HashTable.h"
#include "List.h"

static int finish(Table** const table, const int errorCode)
{
    deleteTable(table);
    return errorCode;
}

static int testHashTable(void)
{
    Table* table = createTable();
    if (table == NULL)
    {
        return 1;
    }
    int errorCode = addWordsToTable(table, "test1 test2");
    if (errorCode != ok)
    {
        return finish(&table, 2);
    }
    if (addToTable(table, "3tset") != ok)
    {
        return finish(&table, 3);
    }
    List* list1 = getList(table, 66);
    List* list2 = getList(table, 67);
    List* list3 = getList(table, 207);
    if (list1 == NULL || list2 == NULL || list3 == NULL || getSize(list1) != 1 || getSize(list2) != 1 || getSize(list3) != 1)
    {
        return finish(&table, 4);
    }
    errorCode = ok;
    if ((int)(loadFactor(table, &errorCode) * 1000000) != 10238 || errorCode != ok)
    {
        return finish(&table, 5);
    }
    if (averageListLength(table, &errorCode) != (float)1 || errorCode != ok)
    {
        return finish(&table, 6);
    }
    if (maxListLength(table, &errorCode) != 1 || errorCode != ok)
    {
        return finish(&table, 7);
    }
    return finish(&table, ok);
}

int tests(void)
{
    const int errorCode = testHashTable();
    if (errorCode != ok)
    {
        printf("ERROR IN HASH TABLE TEST, CASE %d", errorCode);
    }
    return errorCode;
}
