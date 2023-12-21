#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "MyContainers.h"

struct Graph
{
    Vector** vertexes;
    size_t amountOfVertexes;
};

static int tryAddPair(Graph* const graph, const size_t length, const size_t index, const size_t vertex)
{
    Pair* pair = createPair();
    if (pair == NULL)
    {
        return memoryError;
    }
    setSecond(pair, length);
    setFirst(pair, vertex);
    int errorCode = addElement(graph->vertexes[index], pair);
    if (errorCode != ok)
    {
        deletePair(&pair);
        return errorCode;
    }
    return ok;
}

Graph* createGraph(const size_t amountOfVertexes)
{
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->vertexes = (Vector**)calloc(amountOfVertexes, sizeof(Vector*));
    if (graph->vertexes == NULL)
    {
        free(graph);
        return NULL;
    }
    for (size_t i = 0; i < amountOfVertexes; ++i)
    {
        Vector* newVector = createVector();
        if (newVector == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                deleteVector(&graph->vertexes[j]);
            }
            free(graph->vertexes);
            free(graph);
            return NULL;
        }
        graph->vertexes[i] = newVector;
    }
    graph->amountOfVertexes = amountOfVertexes;
    return graph;
}

size_t getAmountOfVertexes(const Graph* const graph)
{
    if (graph == NULL)
    {
        return 0;
    }
    return graph->amountOfVertexes;
}

GraphErrorCode addVertice(Graph* const graph, const size_t firstVertex, const size_t secondVertex, const size_t length)
{
    if (graph == NULL)
    {
        return nullPointerError;
    }
    if (firstVertex >= graph->amountOfVertexes || secondVertex >= graph->amountOfVertexes)
    {
        return indexOutOfRangeError;
    }
    GraphErrorCode errorCode = tryAddPair(graph, length, firstVertex, secondVertex);
    if (errorCode != ok)
    {
        return errorCode;
    }
    errorCode = tryAddPair(graph, length, secondVertex, secondVertex);
    if (errorCode != ok)
    {
        return errorCode;
    }
    return ok;
}

Vector* getAdjacentVertexes(const Graph* const graph, const size_t vertex, GraphErrorCode* const errorCode)
{
    if (graph == NULL)
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    if (vertex >= graph->amountOfVertexes)
    {
        *errorCode = indexOutOfRangeError;
        return NULL;
    }
    return graph->vertexes[vertex];
}

void deleteGraph(Graph** const graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }
    for (size_t i = 0; i < (*graph)->amountOfVertexes; ++i)
    {
        deleteVector(&(*graph)->vertexes[i]);
    }
    free(*graph);
}
