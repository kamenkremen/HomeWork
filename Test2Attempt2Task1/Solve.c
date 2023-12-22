#include <stdlib.h>
#include <stdio.h>

#include "Queue.h"
#include "ErrorCodes.h"

static int readFileFinish(FILE** const file1, const int returnValue)
{
    fclose(*file1);
    return returnValue;
}

static int solveFinish(Queue** const queue1, Queue** const queue2, Queue** const queue3, const int returnValue)
{
    deleteQueue(queue1);
    deleteQueue(queue2);
    deleteQueue(queue3);
    return returnValue;
}

static int readFile(Queue* const firstGroup, Queue* const secondGroup, Queue* const thirdGroup, const int a, const int b, const char* const inputFileName)
{
    FILE* inputFile = NULL;
    fopen_s(&inputFile, inputFileName, "r");
    if (inputFile == NULL)
    {
        return fileError;
    }
    while (true)
    {
        int number = 0;
        int scannedValues = fscanf_s(inputFile, "%d", &number);
        if (scannedValues == EOF)
        {
            break;
        }
        else if (scannedValues != 1)
        {
            return readFileFinish(&inputFile, fileError);
        }
        if (number < a)
        {
            if (enqueue(firstGroup, number) != ok)
            {
                return readFileFinish(&inputFile, memoryError);
            }
        }
        else if (number <= b)
        {
            if (enqueue(secondGroup, number) != ok)
            {
                return readFileFinish(&inputFile, memoryError);
            }
        }
        else
        {
            if (enqueue(thirdGroup, number) != ok)
            {
                return readFileFinish(&inputFile, memoryError);
            }
        }
    }
    return readFileFinish(&inputFile, ok);
}

static int writeQueue(Queue* const queue, FILE* const stream)
{
    int errorCode = ok;
    while (!isEmpty(queue))
    {
        int number = front(queue, &errorCode);
        if (errorCode != ok)
        {
            fclose(stream);
            return errorCode;
        }
        if (fprintf(stream, "%d ", number) < 0)
        {
            fclose(stream);
            return fileError;
        }
        errorCode = dequeue(queue);
        if (errorCode != ok)
        {
            fclose(stream);
            return errorCode;
        }
    }
    return ok;
}

static int writeQueues(Queue* const first, Queue* const second, Queue* const third, const char* const fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "w");
    if (file == NULL)
    {
        return fileError;
    }
    int errorCode = writeQueue(first, file);
    if (errorCode != ok)
    {
        fclose(file);
        return errorCode;
    }
    errorCode = writeQueue(second, file);
    if (errorCode != ok)
    {
        fclose(file);
        return errorCode;
    }
    errorCode = writeQueue(third, file);
    if (errorCode != ok)
    {
        fclose(file);
        return errorCode;
    }
    fclose(file);
    return ok;
}

int solve(const int a, const int b, const char* const inputFileName, const char* const outputFileName)
{
    Queue* firstGroup = createQueue();
    if (firstGroup == NULL)
    {
        return memoryError;
    }
    Queue* secondGroup = createQueue();
    if (secondGroup == NULL)
    {
        deleteQueue(&firstGroup);
        return memoryError;
    }
    Queue* thirdGroup = createQueue();
    if (thirdGroup == NULL)
    {
        deleteQueue(&firstGroup);
        deleteQueue(&secondGroup);
        return memoryError;
    }
    int errorCode = readFile(firstGroup, secondGroup, thirdGroup, a, b, inputFileName);
    if (errorCode != ok)
    {
        return solveFinish(&secondGroup, &thirdGroup, &firstGroup, errorCode);
    }
    errorCode = writeQueues(firstGroup, secondGroup, thirdGroup, outputFileName);
    if (errorCode != ok)
    {
        return solveFinish(&secondGroup, &thirdGroup, &firstGroup, errorCode);
    }
    return solveFinish(&secondGroup, &thirdGroup, &firstGroup, ok);
}
