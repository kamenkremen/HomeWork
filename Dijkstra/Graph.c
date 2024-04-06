#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "MyContainers.h"

struct Graph
{
    Vector** vertices;
    size_t amountOfVertices;
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
    int errorCode = addElement(graph->vertices[index], pair);
    if (errorCode != ok)
    {
        deletePair(&pair);
        return errorCode;
    }
    return ok;
}

Graph* createGraph(const size_t amountOfVertices)
{
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->vertices = (Vector**)calloc(amountOfVertices, sizeof(Vector*));
    if (graph->vertices == NULL)
    {
        free(graph);
        return NULL;
    }
    for (size_t i = 0; i < amountOfVertices; ++i)
    {
        Vector* newVector = createVector();
        if (newVector == NULL)
        {
            for (size_t j = 0; j < i; ++j)
            {
                deleteVector(&graph->vertices[j]);
            }
            free(graph->vertices);
            free(graph);
            return NULL;
        }
        graph->vertices[i] = newVector;
    }
    graph->amountOfVertices = amountOfVertices;
    return graph;
}

size_t getAmountOfVertices(const Graph* const graph)
{
    if (graph == NULL)
    {
        return 0;
    }
    return graph->amountOfVertices;
}

GraphErrorCode addEdge(Graph* const graph, const size_t firstVertex, const size_t secondVertex, const size_t length)
{
    if (graph == NULL)
    {
        return nullPointerError;
    }
    if (firstVertex >= graph->amountOfVertices || secondVertex >= graph->amountOfVertices)
    {
        return indexOutOfRangeError;
    }
    GraphErrorCode errorCode = tryAddPair(graph, length, firstVertex, secondVertex);
    if (errorCode != ok)
    {
        return errorCode;
    }
    errorCode = tryAddPair(graph, length, secondVertex, firstVertex);
    if (errorCode != ok)
    {
        return errorCode;
    }
    return ok;
}

Vector* getAdjacentVertices(const Graph* const graph, const size_t vertex, GraphErrorCode* const errorCode)
{
    if (graph == NULL)
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    if (vertex >= graph->amountOfVertices)
    {
        *errorCode = indexOutOfRangeError;
        return NULL;
    }
    return graph->vertices[vertex];
}

void deleteGraph(Graph** const graph)
{
    if (graph == NULL || *graph == NULL)
    {
        return;
    }
    for (size_t i = 0; i < (*graph)->amountOfVertices; ++i)
    {
        deleteVector(&(*graph)->vertices[i]);
    }
    free(*graph);
}
