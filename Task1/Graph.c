#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Graph.h"
#include "ErrorCodes.h"

struct Graph
{
    bool matrix[6][4];
    size_t vortexes;
    size_t edges;
};

void getAdjacentVortexes(Graph* const graph, const size_t const vortex, int* const errorCode, bool* adjacent)
{
    if (graph == NULL || adjacent == NULL)
    {
        *errorCode = nullPointerError;
        return;
    }
    for (size_t i = 0; i < graph->edges; ++i)
    {
        if (graph->matrix[vortex][i] == true)
        {
            for (size_t j = 0; j < graph->vortexes; ++j)
            {
                if (vortex == j)
                {
                    continue;
                }
                if (graph->matrix[j][i] == true) {
                    adjacent[j] = true;
                }
            }
        }
    }
}

Graph* createGraph(void) 
{
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    const char* matrix = "110001100001000100001010";
    graph->vortexes = 6;
    graph->edges = 4;
    for (size_t i = 0; i < graph->vortexes * graph->edges; ++i)
    {
        graph->matrix[i / 4][i % 4] = (matrix[i] == '1' ? true : false);
    }
    return graph;
}

size_t getVortexes(const Graph* const graph, int* const errorCode)
{
    if (graph == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    return graph->vortexes;
}