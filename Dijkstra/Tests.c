#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"
#include "ErrorCodes.h"
#include "PriorityQueue.h"
#include "MyContainers.h"
#include "Tests.h"
#include "DijkstraSolve.h"

static int finish(Graph** const graph, size_t** const used, size_t** const capitals, const int returnValue)
{
    deleteGraph(graph);
    if (used != NULL)
    {
        free(*used);
    }
    free(*capitals);
    return returnValue;
}

static int parseTest(void)
{
    size_t n = 0;
    size_t m = 0;
    size_t k = 0;
    int errorCode = ok;
    Graph* graph = NULL;
    size_t* capitals = parseFile("test1.txt", &n, &m, &k, &graph, &errorCode);
    deleteGraph(&graph);
    if (errorCode != ok)
    {
        return 2;
    }
    const size_t capital = capitals[0];
    free(capitals);
    if (n != 3 || m != 2 || k != 1 || capital != 0)
    {
        return 3;
    }
    return ok;
}

static int solveTest(void)
{
    size_t n = 0;
    size_t m = 0;
    size_t k = 0;
    int errorCode = ok;
    Graph* graph = NULL;
    size_t* capitals = parseFile("test2.txt", &n, &m, &k, &graph, &errorCode);
    if (errorCode != ok)
    {
        return 2;
    }

    size_t* used = NULL;
    errorCode = solve(n, m, k, graph, capitals, &used);
    if (used == NULL)
    {
        return finish(&graph, NULL, &capitals, 3);
    }
    if (errorCode != ok)
    {
        return finish(&graph, &used, &capitals, 4);
    }
    if (used[0] != 1 || used[1] != 2 || used[2] != 1 || used[3] != 2)
    {
        return finish(&graph, &used, &capitals, 5);
    }
    return finish(&graph, &used, &capitals, ok);
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
