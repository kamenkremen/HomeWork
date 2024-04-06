#include <stdlib.h>

#include "MyContainers.h"
#include "ErrorCodes.h"

struct Pair
{
    PairValueType first;
    PairValueType second;
};

Pair* createPair(void)
{
    return (Pair*)calloc(1, sizeof(Pair));
}

PairValueType getFirst(const Pair* const pair, Error* const errorCode)
{
    if (pair == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    return pair->first;
}

PairValueType getSecond(const Pair* const pair, Error* const errorCode)
{
    if (pair == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    return pair->second;
}

void deletePair(Pair** const pair)
{
    if (pair == NULL || *pair == NULL)
    {
        return;
    }
    free(*pair);
}

Error setFirst(Pair* const pair, const PairValueType first)
{
    if (pair == NULL)
    {
        return nullPointerError;
    }
    pair->first = first;
}

Error setSecond(Pair* const pair, const PairValueType second)
{
    if (pair == NULL)
    {
        return nullPointerError;
    }
    pair->second = second;
}
