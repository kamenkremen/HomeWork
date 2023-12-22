#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "PriorityQueue.h"
#include "MyContainers.h"

size_t* parseFile(const char* const fileName, size_t* const n, size_t* const m, size_t* const k, Graph** const graph, int* const errorCode)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        *errorCode = memoryError;
        return NULL;
    }
    if (fscanf_s(file, "%zu %zu", n, m) != 2)
    {
        *errorCode = inputError;
        return NULL;
    }
    *graph = createGraph(*n);
    if (*graph == NULL)
    {
        *errorCode = memoryError;
        return NULL;
    }
    for (size_t z = 0; z < *m; ++z)
    {
        size_t i = 0;
        size_t j = 0;
        size_t length = 0;
        if (fscanf_s(file, "%zu %zu %zu", &i, &j, &length) != 3)
        {
            *errorCode = inputError;
            deleteGraph(graph);
            return NULL;
        }
        --i;
        --j;
        *errorCode = addVertice(*graph, i, j, length);
        if (*errorCode != ok)
        {
            deleteGraph(graph);
            return NULL;
        }
    }
    if (fscanf_s(file, "%zu", k) != 1)
    {
        *errorCode = inputError;
        deleteGraph(graph);
        return NULL;
    }

    size_t* capitals = (size_t*)calloc(*k, sizeof(size_t));
    for (size_t current = 0; current < *k; ++current)
    {
        size_t x = 0;
        if (fscanf_s(file, "%zu", &x) != 1)
        {
            free(capitals);
            deleteGraph(graph);
            *errorCode = inputError;
            return NULL;
        }
        --x;
        capitals[current] = x;
    }
    return capitals;
}

static int finish(PriorityQueue** const nations, int* const distances, size_t* const used, const size_t size, const int returnCode)
{
    free(distances);
    free(used);
    for (size_t i = 0; i < size; ++i)
    {
        deleteQueue(&nations[i]);
    }
    free(nations);
    return returnCode;
}

int solve(const size_t n, const size_t m, const size_t k, const Graph* const graph, const size_t* const capitals, size_t** const used)
{
    PriorityQueue** nations = (PriorityQueue**)calloc(k, sizeof(PriorityQueue*));
    int errorCode = ok;
    if (nations == NULL)
    {
        return memoryError;
    }
    *used = (size_t*)calloc(n, sizeof(size_t));
    if (*used == NULL)
    {
        free(nations);
        return memoryError;
    }
    size_t* distances = (size_t*)calloc(n, sizeof(size_t));
    if (distances == NULL)
    {
        free(nations);
        free(*used);
        return memoryError;
    }
    for (size_t i = 0; i < k; ++i)
    {
        nations[i] = createPriorityQueue();
        if (nations[i] == NULL || insert(nations[i], capitals[i], 0) != ok)
        {
            return finish(nations, distances, *used, i, memoryError);
        }
    }
    size_t remaining = n;

    while (remaining != 0)
    {
        for (size_t i = 0; i < k && remaining != 0; ++i)
        {
            if (getSize(nations[i]) == 0)
            {
                continue;
            }
            size_t length = 0;
            size_t current = pop(nations[i], &length, &errorCode);
            if (errorCode != ok)
            {
                return finish(nations, distances, *used, k, errorCode);
            }
            while (getSize(nations[i]) != 0 && (*used)[current] != 0)
            {
                current = pop(nations[i], &length, &errorCode);
                if (errorCode != ok)
                {
                    return finish(nations, distances, *used, k, errorCode);
                }
            }
            if ((*used)[current] != 0)
            {
                continue;
            }
            (*used)[current] = i + 1;
            distances[current] = length;
            --remaining;
            Vector* vertexes = getAdjacentVertexes(graph, current, &errorCode);
            if (errorCode != ok)
            {
                return finish(nations, distances, *used, k, errorCode);
            }
            size_t size = getVectorSize(vertexes);
            for (size_t j = 0; j < size; ++j)
            {
                Pair* currentElement = getElement(vertexes, j, &errorCode);
                if (currentElement == NULL)
                {
                    continue;
                }
                if ((*used)[getFirst(currentElement, &errorCode)] != 0)
                {
                    continue;
                }
                errorCode = insert(nations[i], getFirst(currentElement, &errorCode), getSecond(currentElement, &errorCode) + distances[current]);
                if (errorCode != ok)
                {
                    return finish(nations, distances, *used, k, errorCode);
                }
            }
        }
    }
    return finish(nations, distances, NULL, k, ok);
}
