#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ErrorCodes.h"
#include "AVL.h"

typedef struct Node
{
    struct Node* rightChild;
    struct Node* leftChild;
    int height;
    char* value;
    char* key;
} Node;

struct Tree
{
    Node* root;
};

static int getHeight(const Node* const node)
{
    return (node == NULL) ? -1 : node->height;
}

static void updateHeight(Node* const node)
{
    int heightLeft = 0;
    int heightRight = 0;
    heightLeft = getHeight(node->leftChild);
    heightRight = getHeight(node->rightChild);
    node->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
}

static int getBalance(const Node* const node)
{
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

static Node* rotateLeft(Node* const a)
{
    Node* b = a->rightChild;
    Node* c = b->leftChild;
    b->leftChild = a;
    a->rightChild = c;
    updateHeight(a);
    updateHeight(b);
    return b;
}

static Node* rotateRight(Node* const a)
{
    Node* b = a->leftChild;
    Node* c = b->rightChild;
    b->rightChild = a;
    a->leftChild = c;
    updateHeight(a);
    updateHeight(b);
    return b;
}

static Node* bigRotateLeft(Node* const a)
{
    a->rightChild = rotateRight(a->rightChild);
    return rotateLeft(a);
}

static Node* bigRotateRight(Node* const a)
{
    a->leftChild = rotateLeft(a->leftChild);
    return rotateRight(a);
}

static Node* balance(const Node* const a)
{
    if (a == NULL)
    {
        return NULL;
    }
    if (getBalance(a) == -2)
    {
        if (getBalance(a->rightChild) <= 0) {
            return rotateLeft(a);
        }
        return bigRotateLeft(a);
    }
    if (getBalance(a) == 2)
    {
        if (getBalance(a->rightChild) > 0)
        {
            return rotateRight(a);
        }
        return bigRotateRight(a);
    }
    return a;
}

static Node* insertStatic(Node* node, const char* value, const char* key, int* const errorCode)
{
    if (node == NULL)
    {
        Node* newNode = (Node*)calloc(1, sizeof(Node));
        if (newNode == NULL)
        {
            return NULL;
        }
        newNode->key = (char*)calloc(strlen(key), sizeof(char));
        if (newNode->key == NULL)
        {
            *errorCode = memoryError;
            free(newNode);
            return NULL;
        }
        newNode->value = (char*)calloc(strlen(value), sizeof(char));
        if (newNode->value == NULL)
        {
            *errorCode = memoryError;
            free(newNode->key);
            free(newNode);
            return NULL;
        }
        strcpy(newNode->key, key);
        strcpy(newNode->value, value);
        newNode->height = 0;
        return newNode;
    }
    int compare = strcmp(key, node->key);
    if (compare > 0)
    {
        node->rightChild = insertStatic(node->rightChild, value, key, errorCode);
    }
    else if (compare < 0)
    {
        node->leftChild = insertStatic(node->leftChild, value, key, errorCode);
    }
    else
    {
        node->value = (char*)calloc(strlen(value), sizeof(char));
        if (node->value == NULL)
        {
            *errorCode = memoryError;
            return NULL;
        }
        strcpy(node->value, value);
    }
    updateHeight(node);
    node = balance(node);
    return node;
}

int insert(Tree* const tree, const char* value, const char* key)
{
    int errorCode = ok;
    if (tree == NULL)
    {
        return nullPointerError;
    }
    tree->root = insertStatic(tree->root, value, key, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }
    return ok;
}

static char* getValueStatic(const Node* const node, const char* key)
{
    if (node == NULL)
    {
        return NULL;
    }
    const int compare = strcmp(key, node->key);
    return compare == 0 ? node->value : (compare > 0 ? getValueStatic(node->rightChild, key) : getValueStatic(node->leftChild, key));
}

char* getValue(const Tree* const tree, const char* key)
{
    if (tree == NULL)
    {
        return NULL;
    }
    return getValueStatic(tree->root, key);
}

bool isContains(const Tree* const tree, const char* key)
{
    return (getValue(tree, key) != NULL);
}

static void updateHeightToNode(Node* const start, Node* const end)
{
    if (start == end)
    {
        updateHeight(start);
        return;
    }
    updateHeightToNode(start->leftChild, end);
    updateHeight(start);
}

static Node* deleteNode(const Node* const node)
{
    if (node == NULL)
    {
        return node;
    }
    if (node->rightChild == NULL)
    {
        Node* buffer = node->leftChild;;
        free(node);
        return buffer;
    }
    if (node->rightChild->leftChild == NULL)
    {
        node->rightChild->leftChild = node->leftChild;
        Node* buffer = node->rightChild;
        free(node);
        return buffer;
    }
    Node* previous = node;
    Node* current = node->rightChild;
    for (; current->leftChild != NULL; previous = current, current = current->leftChild);
    previous->leftChild = current->rightChild;
    current->rightChild = node->rightChild;
    current->leftChild = node->leftChild;
    updateHeightToNode(current->rightChild, previous);
    updateHeight(current);
    free(node);
    return current;

}

static Node* deleteElementStatic(Node* node, const char* key)
{
    if (node == NULL)
    {
        return;
    }
    int compare = strcmp(key, node->key);
    if (compare > 0)
    {
        node->rightChild = deleteElementStatic(node->rightChild, key);
    }
    else if (compare < 0)
    {
        node->leftChild = deleteElementStatic(node->leftChild, key);
    }
    else
    {
        node = deleteNode(node);
    }
    if (node == NULL)
    {
        return node;
    }
    updateHeight(node);
    node = balance(node);
    return node;
}

bool deleteElement(Tree* const tree, const char* key)
{
    if (tree == NULL)
    {
        return true;
    }
    tree->root = deleteElementStatic(tree->root, key);
    return false;
}

Tree* createTree(void)
{
    return (Tree*)calloc(1, sizeof(Tree));
}

static void deleteSubTrees(Node** const node)
{
    if (node == NULL || *node == NULL)
    {
        return;
    }
    deleteSubTrees((*node)->leftChild);
    deleteSubTrees((*node)->rightChild);
    free(*node);
}

void deleteTree(Tree** const tree)
{
    deleteSubTrees(&((*tree)->root));
    free(*tree);
}
