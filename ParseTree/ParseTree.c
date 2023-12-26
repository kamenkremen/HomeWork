#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "ParseTree.h"
#include "ErrorCodes.h"

typedef struct Node
{
    bool isOperation;
    int value;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;


struct ParseTree
{
    Node* root;
};

static void deleteSubTree(Node* const node)
{
    if (node == NULL)
    {
        return;
    }
    deleteSubTree(node->rightChild);
    deleteSubTree(node->leftChild);
    free(node);
}

static bool isOperation(const char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

static int getNumber(const char* const expression, size_t* const index, const size_t length)
{
    int number = 0;
    for (; *index < length && (bool)isdigit(expression[*index]); ++(*index))
    {
        number = number * 10 + (int)expression[*index] - (int)'0';
    }
    return number;
}

static Node* createNode(const char* const expression, size_t* const index, const size_t length)
{
    for (; *index < length && (expression[*index] == ' ' || expression[*index] == '(' || expression[*index] == ')'); ++(*index));
    if (*index == length)
    {
        return NULL;
    }
    Node* newNode = (Node*)calloc(1, sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }
    if (isOperation(expression[*index]))
    {
        if (expression[*index] == '-' && expression[*index + 1] != ' ')
        {
            ++(*index);
            newNode->value = -getNumber(expression, index, length);
            return newNode;
        }
        newNode->isOperation = true;
        newNode->value = (int)expression[*index];
        ++(*index);
        newNode->leftChild = createNode(expression, index, length);
        if (newNode->leftChild == NULL)
        {
            free(newNode);
            return NULL;
        }
        ++(*index);
        newNode->rightChild = createNode(expression, index, length);
        if (newNode->rightChild == NULL)
        {
            deleteSubTree(newNode);
            return NULL;
        }
    }
    else
    {
        newNode->value = getNumber(expression, index, length);
    }
    return newNode;
}

static bool isCorrect(const char* const expression, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        const char currentChar = expression[i];
        if (currentChar == '(')
        {
            if (i == length || !isOperation(expression[i + 1]))
            {
                return false;
            }
        }
        if (isOperation(expression[i]))
        {
            if (i == 0 || expression[i - 1] != '(')
            {
                return false;
            }
        }
        else if (currentChar != ' ' && currentChar != '(' && currentChar != ')' && !(bool)isdigit(currentChar))
        {
            return false;
        }
    }
    return true;
}

ParseTree* build(const char* const expression)
{
    if (expression == NULL)
    {
        return NULL;
    }
    const size_t length = strlen(expression);
    if (!isCorrect(expression, length))
    {
        return NULL;
    }
    ParseTree* tree = (ParseTree*)calloc(1, sizeof(ParseTree));
    if (tree == NULL)
    {
        return NULL;
    }
    size_t index = 0;
    tree->root = createNode(expression, &index, length);
    if (index + 1 < length)
    {
        deleteParseTree(&tree);
    }
    return tree;
}

static void printNode(const Node* const node)
{
    if (node->leftChild == NULL && node->rightChild == NULL)
    {
        printf("%d", node->value);
        return;
    }
    printf("(%c ", (char)node->value);
    printNode(node->leftChild);
    printf(" ");
    printNode(node->rightChild);
    printf(")");
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

void deleteParseTree(ParseTree** const tree)
{
    deleteSubTree((*tree)->root);
    free(*tree);
    *tree = NULL;
}

static int proceedOperation(const int first, const int second, const char operation, int* const errorCode)
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
            if (second == 0)
            {
                *errorCode = nullDivisionError;
                return 0;
            }
            return first / second;
        default:
            return 0;
    }
}

static int calculateSubtree(const Node* const node, int* const errorCode)
{
    if (node == NULL)
    {
        return 0;
    }
    if (!node->isOperation)
    {
        return node->value;
    }
    const int leftResult = calculateSubtree(node->leftChild, errorCode);
    if (*errorCode != ok)
    {
        return 0;
    }
    const int rightResult = calculateSubtree(node->rightChild, errorCode);
    if (*errorCode != ok)
    {
        return 0;
    }
    const int result = proceedOperation(leftResult, rightResult, (char)node->value, errorCode);
    if (*errorCode != ok)
    {
        return 0;
    }
    return result;
}

int calculate(const ParseTree* const tree, int* const errorCode)
{
    if (tree == NULL)
    {
        *errorCode = nullPointerError;
        return 0;
    }
    if (tree->root == NULL)
    {
        return 0;
    }
    return calculateSubtree(tree->root, errorCode);
}
