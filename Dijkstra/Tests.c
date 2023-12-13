#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "PriorityQueue.h"
#include "MyContainers.h"
#include "Tests.h"
#include "DijkstraSolve.h"

static int parseTest(void)
{
    size_t n = 0;
    size_t m = 0;
    size_t k = 0;
    int errorCode = ok;
    Graph* graph = createGraph();
    if (graph == NULL)
    {
        return 1;
    }
    size_t* capitals = parseFile("test1.txt", &n, &m, &k, graph, &errorCode);
    if (errorCode != ok)
    {
        deleteGraph(&graph);
        return 2;
    }
    deleteGraph(&graph);
    if (n != 3 || m != 2 || k != 1 || capitals[0] != 0)
    {
        free(capitals);
        return 3;
    }
    free(capitals);
    return ok;
}

static int solveTest(void)
{
    size_t n = 0;
    size_t m = 0;
    size_t k = 0;
    int errorCode = ok;
    Graph* graph = createGraph();
    if (graph == NULL)
    {
        return 1;
    }
    size_t* capitals = parseFile("test2.txt", &n, &m, &k, graph, &errorCode);
    if (errorCode != ok)
    {
        deleteGraph(&graph);
        return 2;
    }
    size_t* used = (size_t*)calloc(n, sizeof(size_t));
    if (used == NULL)
    {
        deleteGraph(&graph);
        free(capitals);
        return 3;
    }
    errorCode = solve(n, m, k, graph, capitals, used);
    if (errorCode != ok)
    {
        free(used);
        deleteGraph(&graph);
        free(capitals);
        return 4;
    }
    if (used[0] != 1 || used[1] != 2 || used[2] != 1 || used[3] != 2)
    {
        free(used);
        deleteGraph(&graph);
        free(capitals);
        return 5;
    }
    free(used);
    deleteGraph(&graph);
    free(capitals);
    return ok;
}

int tests(void)
{
    int error = ok;
    int errorCode = parseTest();
    if (errorCode != ok)
    {
        printf("ERROR IN PARSE TEST, CASE %d\n", errorCode);
        error = errorCode;
    }
    errorCode = solveTest();
    if (errorCode != ok)
    {
        printf("ERROR IN SOLVE TEST, CASE %d\n", errorCode);
        error = errorCode;
    }
    return error;
}
