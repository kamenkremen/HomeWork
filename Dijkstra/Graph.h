#pragma once
#include "MyContainers.h"
typedef struct Graph Graph;

typedef int GraphErrorCode;

Graph* createGraph(void);

size_t getAmountOfVortexes(const Graph* const graph);

GraphErrorCode addVortex(Graph* const graph);

GraphErrorCode addEdge(Graph* const graph, const size_t firstVortex, const size_t secondVortex, const size_t length);

Vector* getAdjacentVortexes(const Graph* const graph, const size_t vortex, GraphErrorCode* const errorCode);

void deleteGraph(Graph** const graph);