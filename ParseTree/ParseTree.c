#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ParseTree.h"
#include "ErrorCodes.h"

typedef struct Node
{
    char operation;
    int number;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;


struct ParseTree
{
    Node* root;
};

bool isOperand(const char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

static getNumber(const char* expression, size_t* index)
{
    int number = 0;
    for (; *index < strlen(expression) && expression[*index] >= '0' && expression[*index] <= '9'; ++(*index))
    {
        number = number * 10 + expression[*index] - '0';
    }
    return number;
}

static Node* createNode(const char* const expression, size_t* index)
{
    ++(*index);
    for (; *index < strlen(expression) && (expression[*index] == ' ' || expression[*index] == '(' || expression[*index] == ')'); ++(*index));
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    if (isOperand(expression[*index]))
    {
        if (expression[*index] == '-' && expression[*index + 1] != ' ')
        {
            ++(*index);
            newNode->number = -getNumber(expression, index);
            return newNode;
        }
        newNode->operation = expression[*index];
        newNode->leftChild = createNode(expression, index);
        newNode->rightChild = createNode(expression, index);
    }
    else
    {
        newNode->number = getNumber(expression, index);
    }
    return newNode;
}

ParseTree* build(const char* const expression)
{
    ParseTree* tree = (ParseTree*)calloc(1, sizeof(ParseTree));
    if (tree == NULL)
    {
        return NULL;
    }
    size_t index = 0;
    tree->root = createNode(expression, &index);
    return tree;
}

static void printNode(const Node* const node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->leftChild == NULL && node->rightChild == NULL)
    {
        printf("%d ", node->number);
        
        return;
    }
    printf("%c ", node->operation);
    printNode(node->leftChild);
    printNode(node->rightChild);
}

void printTree(const ParseTree* const tree)
{   
    if (tree == NULL)
    {
        return;
    }
    printNode(tree->root);
    printf("\n");
}

static void deleteChilds(Node* const node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->rightChild != NULL)
    {
        deleteChilds(node->rightChild);
        free(node->rightChild);
    }
    if (node->leftChild != NULL)
    {
        deleteChilds(node->leftChild);
        free(node->leftChild);
    }
}

void deleteParseTree(ParseTree** const tree)
{
    deleteChilds((*tree)->root);
    free((*tree)->root);
    free(*tree);
}

static int proceedOperation(const int first, const int second, const char operation)
{
    switch (operation)
    {
        case '+':
            return first + second;
        case '-':
            return first - second;
        case'*':
            return first * second;
        case '/':
            return first / second;
    }
}

static int calculateSubtree(const Node* const node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->rightChild != NULL || node->leftChild != NULL ? proceedOperation(calculateSubtree(node->leftChild), 
        calculateSubtree(node->rightChild), node->operation) : node->number;
}

int calculate(const ParseTree* const tree, int* const errorCode)
{
    if (tree == NULL)
    {
        *errorCode = nullPointerError;
        return nullPointerError;
    }
    if (tree->root == NULL)
    {
        return 0;
    }
    return calculateSubtree(tree->root);
}
