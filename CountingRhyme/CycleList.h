#pragma once

#include <stdbool.h>

typedef int listValue;

typedef struct CycleList CycleList;

typedef struct Position Position;

Position* getStartPosition(const CycleList* const list);

bool movePostionForward(Position* const position);

void deletePosition(Position** const position);

CycleList* createList(void);

bool addElement(CycleList* const list, const listValue value);

void deleteList(CycleList** const list);

listValue top(const CycleList* const list, int* const errorCode);

size_t getSize(const CycleList* const list);

bool deleteElement(CycleList* const list, const Position* const position);
