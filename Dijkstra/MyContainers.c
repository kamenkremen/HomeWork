#include <stdlib.h>

#include "MyContainers.h"
#include "ErrorCodes.h"

struct Pair
{
    PairValueType first;
    PairValueType second;
};

struct Vector
{
    size_t size;
    size_t capacity;
    VectorValueType* elements;
};

Pair* createPair(void)
{
    return (Pair*)calloc(1, sizeof(Pair));
}

Vector* createVector(void)
{
    Vector* vector = (Vector*)calloc(1, sizeof(Vector));
    if (vector == NULL)
    {
        return NULL;
    }
    vector->capacity = 1;
    vector->elements = (VectorValueType*)calloc(1, sizeof(VectorValueType));
    if (vector->elements == NULL)
    {
        free(vector);
        return NULL;
    }
    return vector;
}

PairValueType getFirst(const Pair* const pair, Error* const errorCode)
{
    if (pair == NULL)
    {
        *errorCode = nullPointerError;
        return DEFAULT_PAIR_VALUE;
    }
    return pair->first;
}

PairValueType getSecond(const Pair* const pair, Error* const errorCode)
{
    if (pair == NULL)
    {
        *errorCode = nullPointerError;
        return DEFAULT_PAIR_VALUE;
    }
    return pair->second;
}

VectorValueType getElement(const Vector* const vector, const size_t index, Error* const errorCode)
{
    if (vector == NULL)
    {
        *errorCode = nullPointerError;
        return DEFAULT_VECTOR_VALUE;
    }
    if (vector->size <= index)
    {
        *errorCode = indexOutOfRangeError;
        return DEFAULT_VECTOR_VALUE;
    }
    return vector->elements[index];
}

Error addElement(Vector* const vector, const VectorValueType element)
{
    if (vector == NULL)
    {
        return nullPointerError;
    }
    ++vector->size;
    if (vector->capacity < vector->size)
    {
        vector->capacity *= 2;
        VectorValueType* buffer = (VectorValueType*)realloc(vector->elements, vector->capacity * sizeof(VectorValueType));
        if (buffer == NULL)
        {
            deleteVector(&vector);
            return memoryError;
        }
        for (size_t i = 0; i < vector->size; ++i)
        {
            vector->elements[i] = NULL;
        }
        vector->elements = buffer;
        for (size_t i = vector->size; i < vector->capacity; ++i)
        {
            vector->elements[i] = NULL;
        }
    }
    vector->elements[vector->size - 1] = element;
    return ok;
}

size_t getVectorSize(const Vector* const vector)
{
    if (vector == NULL)
    {
        return 0;
    }
    return vector->size;
}

void deleteVector(Vector** const vector)
{
    if (vector == NULL || *vector == NULL)
    {
        return;
    }
    for (size_t i = 0; i < (*vector)->size; ++i)
    {
        deletePair(&(*vector)->elements[i]);
    }
    free((*vector)->elements);
    free(*vector);
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
    return ok;
}

Error setSecond(Pair* const pair, const PairValueType second)
{
    if (pair == NULL)
    {
        return nullPointerError;
    }
    pair->second = second;
    return ok;
}
