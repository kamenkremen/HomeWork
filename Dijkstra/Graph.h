#pragma once

#include "MyContainers.h"

typedef struct Graph Graph;

typedef int GraphErrorCode;

Graph* createGraph(const size_t amountOfVertexes);

size_t getAmountOfVertexes(const Graph* const graph);

GraphErrorCode addVertice(Graph* const graph, const size_t firstVertex, const size_t secondVertex, const size_t length);

Vector* getAdjacentVertexes(const Graph* const graph, const size_t vertex, GraphErrorCode* const errorCode);

void deleteGraph(Graph** const graph);
