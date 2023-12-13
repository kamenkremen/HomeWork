#pragma once

// graph
typedef struct Graph Graph;

// creates graph
Graph* createGraph(const char* const matrix, const size_t size);

// returns amount of all of the vortexes
size_t getAmountOfVortexes(const Graph* const graph);

// returns array of the adjacent vortexes to the vortex
size_t* getAdjacentVortexes(const Graph* const graph, const size_t vortex, size_t* const size, int* const errorCode);

// deletes graph
void deleteGraph(Graph** const graph);