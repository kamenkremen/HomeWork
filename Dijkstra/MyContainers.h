#pragma once

#include <stdlib.h>

#define DEFAULT_PAIR_VALUE 0

#define DEFAULT_VECTOR_VALUE NULL

typedef size_t PairValueType;

typedef struct Pair Pair;

typedef struct Vector Vector;

typedef Pair* VectorValueType;

typedef int Error;

PairValueType getFirst(const Pair* const pair, Error* const errorCode);

PairValueType getSecond(const Pair* const pair, Error* const errorCode);

Pair* createPair(void);

void deletePair(Pair** const pair);

Error setFirst(Pair* const pair, const PairValueType first);

Error setSecond(Pair* const pair, const PairValueType second);

Vector* createVector(void);

VectorValueType getElement(const Vector* const vector, const size_t index, Error* const errorCode);

Error addElement(Vector* const vector, const VectorValueType element);

size_t getVectorSize(const Vector* const vector);

void deleteVector(Vector** const vector);
