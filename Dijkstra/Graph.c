#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "MyContainers.h"


struct Graph
{
    Vector** vortexes;
    size_t amountOfVortexes;
};

Graph* createGraph(void)
{
    return (Graph*)calloc(1, sizeof(Graph));
}

size_t getAmountOfVortexes(const Graph* const graph)
{
    if (graph == NULL)
    {
        return 0;
    }
    return graph->amountOfVortexes;
}

GraphErrorCode addVortex(Graph* const graph)
{
    if (graph == NULL)
    {
        return nullPointerError;
    }
    ++graph->amountOfVortexes;
    graph->vortexes = (Pair***)realloc(graph->vortexes, graph->amountOfVortexes * sizeof(Vector*));
    if (graph->vortexes == NULL)
    {
        return memoryError;
    }
    Vector* newVector = createVector();
    if (newVector == NULL)
    {
        return memoryError;
    }
    graph->vortexes[graph->amountOfVortexes - 1] = newVector;
    return ok;
}

GraphErrorCode addEdge(Graph* const graph, const size_t firstVortex, const size_t secondVortex, const size_t length)
{
    if (graph == NULL)
    {
        return nullPointerError;
    }
    if (firstVortex >= graph->amountOfVortexes || secondVortex >= graph->amountOfVortexes)
    {
        return indexOutOfRangeError;
    }
    Pair* firstPair = createPair();
    if (firstPair == NULL)
    {
        return memoryError;
    }
    setSecond(firstPair, length);
    setFirst(firstPair, secondVortex);
    int errorCode = addElement(graph->vortexes[firstVortex], firstPair);
    if (errorCode != ok)
    {
        deletePair(&firstPair);
        return errorCode;
    }
    Pair* secondPair = createPair();
    if (secondPair == NULL)
    {
        return memoryError;
    }
    setSecond(secondPair, length);
    setFirst(secondPair, secondVortex);
    errorCode = addElement(graph->vortexes[secondVortex], secondPair);
    if (errorCode != ok)
    {
        deletePair(&secondPair);
        return errorCode;
    }
    return ok;
}

Vector* getAdjacentVortexes(const Graph* const graph, const size_t vortex, GraphErrorCode* const errorCode)
{
    if (graph == NULL)
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    if (vortex >= graph->amountOfVortexes)
    {
        *errorCode = indexOutOfRangeError;
        return indexOutOfRangeError;
    }
    return graph->vortexes[vortex];
}

void deleteGraph(Graph** const graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }
    for (size_t i = 0; i < (*graph)->amountOfVortexes; ++i)
    {
        deleteVector(&(*graph)->vortexes[i]);
    }
    free(*graph);
}
