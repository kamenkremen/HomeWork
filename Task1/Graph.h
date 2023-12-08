#pragma once
#include <stdlib.h>
typedef struct Graph Graph;

void getAdjacentVortexes(Graph* const graph, const size_t const vortex, int* const errorCode, bool* adjacent);
Graph* createGraph(void);
size_t getVortexes(const Graph* const graph, int* const errorCode);