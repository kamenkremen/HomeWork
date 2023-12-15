#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FILE_NAME "input.txt"

char* readFile(const char* const fileName)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return NULL;
    }
    char* string = (char*)calloc(1, sizeof(char));
    if (string == NULL)
    {
        fclose(file);
        return NULL;
    }
    size_t capacity = 1;
    size_t length = 0;
    char symbol = 0;
    while ((symbol = getc(file)) != EOF)
    {
        if (length >= capacity)
        {
            capacity *= 2;
            string = (char*)realloc(string, capacity);
            if (string == NULL)
            {
                return NULL;
            }
        }
        if (length != 0 && string[length - 1] == symbol)
        {
            continue;
        }
        string[length] = symbol;
        ++length;
    }
    if (length >= capacity)
    {
        ++capacity;
        string = (char*)realloc(string, capacity);
        if (string == NULL)
        {
            return NULL;
        }
    }
    string[length] = '\0';
    return string;
}

int tests(void)
{
    char* result = readFile("test1.txt");
    if (result == NULL || strcmp(result, "afgba") != 0)
    {
        free(result);
        return 1;
    }
    result = readFile("test2.txt");
    if (result == NULL || strcmp(result, "afg\tgba\na") != 0)
    {
        free(result);
        return 2;
    }
    result = readFile("test3.txt");
    if (result == NULL || strcmp(result, "") != 0)
    {
        free(result);
        return 3;
    }
    result = readFile("test4.txt");
    if (result == NULL || strcmp(result, "programirovanie lublu ochen\n") != 0)
    {
        free(result);
        return 4;
    }
    free(result);
    return 0;
}

int main(void)
{
    int errorCode = tests();
    if (errorCode != 0)
    {
        printf("ERROR IN TEST %d\n", errorCode);
        return errorCode;
    }
    const char* const result = readFile(FILE_NAME);
    if (result == NULL)
    {
        free(result);
        printf("Error in file reading\n");
        return 1;
    }
    printf("Result: %s", result);
    free(result);
    return  0;
}
