#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "PriorityQueue.h"
#include "MyContainers.h"
#include "DijkstraSolve.h"

int main(void)
{
    int errorCode = tests();
    if (errorCode != ok)
    {
        return errorCode;
    }
    size_t n = 0;
    size_t m = 0;
    Graph* graph = createGraph();
    if (graph == NULL)
    {
        printf("MEMORY ERROR\n");
        return memoryError;
    }
    size_t k = 0;
    errorCode = ok;
    size_t* capitals = parseFile("input.txt", &n, &m, &k, graph, &errorCode);
    if (errorCode != ok)
    {
        deleteGraph(&graph);
        printf("ERROR IN FILE READING\n");
        return errorCode;
    }
    size_t* used = (size_t*)calloc(n, sizeof(size_t));
    errorCode = solve(n, m, k, graph, capitals, used);
    if (errorCode != ok)
    {
        printf("ERROR IN SOLVING\n");
        return errorCode;
    }
    printf("Cities that belongs to:\n");
    for (size_t i = 0; i < k; ++i)
    {
        printf("%zu state: ", i + 1);
        for (size_t j = 0; j < n; ++j)
        {
            if (used[j] == i + 1)
            {
                printf("%zu ", j + 1);
            }
        }
        printf("\n");
    }
    return ok;
}
