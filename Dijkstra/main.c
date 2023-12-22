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
    size_t k = 0;
    errorCode = ok;
    Graph* graph = NULL;
    size_t* capitals = parseFile("input.txt", &n, &m, &k, &graph, &errorCode);
    if (errorCode != ok)
    {
        deleteGraph(&graph);
        printf("ERROR IN FILE READING\n");
        return errorCode;
    }
    size_t* used = NULL;
    errorCode = solve(n, m, k, graph, capitals, &used);
    if (errorCode != ok || used == NULL)
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
