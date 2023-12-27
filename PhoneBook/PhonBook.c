#include <stdlib.h>

void freeData(char** const numbers, char** const names, const size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        free(numbers[i]);
        free(names[i]);
    }
}
