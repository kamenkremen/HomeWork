#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "ErrorCodes.h"

struct Graph
{
    bool** vortexes;
    size_t amountOfVortexes;
};

Graph* createGraph(const char* const matrix, const size_t size)
{
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    graph->amountOfVortexes = size;
    graph->vortexes = (bool**)calloc(graph->amountOfVortexes, sizeof(bool*));
    if (graph->vortexes == NULL) {
        free(graph);
        return NULL;
    }
    for (size_t i = 0; i < graph->amountOfVortexes; ++i)
    {
        graph->vortexes[i] = (bool*)calloc(graph->amountOfVortexes, sizeof(bool));
        if (graph->vortexes[i] == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                free(graph->vortexes[j]);
            }
            free(graph->vortexes);
            free(graph);
            return NULL;
        }
    }
    for (size_t i = 0; i < graph->amountOfVortexes; ++i)
    {
        for (size_t j = 0; j < graph->amountOfVortexes; ++j)
        {
            if (matrix[i * graph->amountOfVortexes + j] == '1')
            {
                graph->vortexes[i][j] = true;
            }
        }
    }
    return graph;
}

size_t getAmountOfVortexes(const Graph* const graph)
{
    if (graph == NULL)
    {
        return 0;
    }
    return graph->amountOfVortexes;
}

size_t* getAdjacentVortexes(const Graph* const graph, const size_t vortex, size_t* const size, int* const errorCode)
{
    size_t* result = (size_t*)calloc(graph->amountOfVortexes, sizeof(size_t));
    size_t current = 0;
    if (result == NULL)
    {
        *errorCode = memoryError;
        return NULL;
    }
    for (size_t i = 0; i < graph->amountOfVortexes; ++i)
    {
        if (graph->vortexes[vortex][i])
        {
            result[current] = i;
            ++current;
        }
    }
    *size = current;
    return result;
}


void deleteGraph(Graph** const graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }
    for (size_t i = 0; i < (*graph)->amountOfVortexes; ++i)
    {
        free((*graph)->vortexes[i]);
    }
    free((*graph)->vortexes);
    free(*graph);
}