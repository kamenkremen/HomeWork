#include <stdlib.h>
#include <stdbool.h>

#include "Solve.h"
#include "Graph.h"
#include "ErrorCodes.h"


size_t dfs(const size_t vortex, const Graph* const graph, bool* const used, int* const errorCode)
{
    used[vortex] = true;
    size_t size = 0;
    size_t* adjacent = getAdjacentVortexes(graph, vortex, &size, errorCode);
    if (*errorCode != ok)
    {
        free(adjacent);
        return *errorCode;
    }
    size_t result = 1;
    for (size_t i = 0; i < size; ++i)
    {
        if (!used[adjacent[i]])
        {
            result += dfs(adjacent[i], graph, used, errorCode);
            if (*errorCode != ok)
            {
                free(adjacent);
                return *errorCode;
            }
        }
    }
    free(adjacent);
    return result;
}

size_t* solve(const Graph* const graph, size_t* size, int* const errorCode)
{
    size_t amountOfVortexes = getAmountOfVortexes(graph);
    size_t* result = (size_t*)calloc(amountOfVortexes, sizeof(size_t));
    if (result == NULL)
    {
        *errorCode = memoryError;
        return NULL;
    }
    size_t currentIndex = 0;
    bool* used = (bool*)calloc(amountOfVortexes, sizeof(bool));
    if (used == NULL)
    {
        free(result);
        *errorCode = memoryError;
        return NULL;
    }
    for (size_t i = 0; i < amountOfVortexes; ++i)
    {
        size_t dfsResult = dfs(i, graph, used, errorCode);
        if (*errorCode != ok)
        {
            free(result);
            free(used);
            return NULL;
        }
        if (dfsResult == amountOfVortexes)
        {
            result[currentIndex] = i;
            ++currentIndex;
        }
        for (size_t j = 0; j < amountOfVortexes; ++j)
        {
            used[j] = false;
        }
    }
    free(used);
    *size = currentIndex;
    return result;
}
