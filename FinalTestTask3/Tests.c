#include <stdlib.h>

#include "Solve.h"
#include "Graph.h"
#include "ErrorCodes.h"

int test(void)
{
    int errorCode = ok;
    Graph* graph = createGraph("1110101000101000001000011", 5);
    if (graph == NULL)
    {
        return 1;
    }
    size_t size = 0;
    size_t* result = solve(graph, &size, &errorCode);
    if (size != 2 || result[0] != 0 || result[1] != 2)
    {
        deleteGraph(&graph);
        free(result);
        return 2;
    }
    deleteGraph(&graph);
    free(result);
    return ok;
}