#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Graph.h"
#include "ErrorCodes.h"

int tests(void)
{
    Graph* graph = createGraph();
    if (graph == NULL)
    {
        return 1;
    }
    if (getVortexes(graph) != 6)
    {
        return 2;
    }
    int errorCode = ok;
    bool adjacent[6] = { false };
    getAdjacentVortexes(graph, 0, &errorCode, adjacent);
    if (errorCode != ok || adjacent[5] != true || adjacent[1] != true)
    {
        return 3;
    }
    size_t used[6] = { 0 };
    if (dfs(graph, 0, used, 1) != ok)
    {
        return 4;
    }
    if (used[1] != 1 || used[5] != 1)
    {
        return 5;
    }
    return ok;
}

static int dfs(const Graph* const graph, const size_t vortex, size_t* used, size_t component)
{
    used[vortex] = component;
    int errorCode = ok;
    size_t size = getVortexes(graph);
    bool* adjacent = (bool*)calloc(size, sizeof(bool));
    getAdjacentVortexes(graph, vortex, &errorCode, adjacent);
    if (errorCode != ok)
    {
        return errorCode;
    }
    for (size_t i = 0; i < size; ++i)
    {
        if (adjacent[i])
        {
            if (!used[i])
            {
                if (dfs(graph, i, used, component) != ok)
                {
                    return memoryError;
                }
            }
        }
    }
    return ok;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        printf("ERROR IN %d TEST\n", errorCode);
        return errorCode;
    }
    Graph* graph = createGraph();
    size_t amountOfVortexes = getVortexes(graph);
    size_t* used = (size_t*)calloc(amountOfVortexes, sizeof(size_t));
    if (used == NULL)
    {
        printf("MEMORY ERROR\n");
        free(graph);
        return memoryError;
    }
    size_t currentComponent = 1;
    for (size_t i = 0; i < amountOfVortexes; ++i)
    {
        if (used[i] == 0)
        {
            int errorCode = dfs(graph, i, used, currentComponent);
            if (errorCode != ok)
            {
                printf("MEMORY ERROR\n");
                free(used);
                free(graph);
                return memoryError;
            }
            ++currentComponent;
        }
    }
    for (size_t i = 1; i < currentComponent; ++i)
    {
        printf("%zu component: ", i);
        for (size_t j = 0; j < amountOfVortexes; ++j)
        {
            if (used[j] == i) {
                printf("%zu ", j + 1);
            }
        }
        printf("\n");
    }
    return 0;
}