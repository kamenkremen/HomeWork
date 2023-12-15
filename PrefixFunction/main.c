#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Files.h"
#include "Strings.h"
#include "ErrorCodes.h"

int main(void)
{
    int* s = prefixFunction("aboba", "boba");
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%d ", s[i]);
    }
    printf("\n");
}