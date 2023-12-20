#pragma once

#include <stdlib.h>
// value type of the pair
typedef size_t PairValueType;
// the pair
typedef struct Pair Pair;
// pair error code
typedef int Error;
// returns first element of the pair
PairValueType getFirst(const Pair* const pair, Error* const errorCode);
// returns second element of the pair
PairValueType getSecond(const Pair* const pair, Error* const errorCode);
// returns pair
Pair* createPair(void);
// deletes pair
void deletePair(Pair** const pair);
// sets the first element of the pair
Error setFirst(Pair* const pair, const PairValueType first);
// sets the second element of the pair
Error setSecond(Pair* const pair, const PairValueType second);
