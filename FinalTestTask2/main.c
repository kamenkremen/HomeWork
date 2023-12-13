#include <stdlib.h>
#include <stdio.h>

#include "PriorityQueue.h"
#include "ErrorCodes.h"

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    else
    {
        printf("All tests has been successfully passed.\n");
    }
    return ok;
}
