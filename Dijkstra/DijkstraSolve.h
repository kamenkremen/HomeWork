#pragma once
#include "Graph.h"
size_t* parseFile(const char* const fileName, size_t* const n, size_t* const m, size_t* const k, Graph* const graph, int* const errorCode);
int solve(const size_t n, const size_t m, const size_t k, const Graph* const graph, const size_t* const capitals, size_t* const used);