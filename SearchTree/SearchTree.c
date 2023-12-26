#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SearchTree.h"
#include "Strings.h"

typedef struct TreeElement
{
    struct TreeElement* leftChild;
    struct TreeElement* rightChild;
    int key;
    char* value;
} TreeElement;

struct Tree
{
    TreeElement* root;
};

static void freeNode(TreeElement* node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->value);
    free(node);
}

Tree* createTree(void)
{
    return (Tree*)calloc(1, sizeof(Tree));
}

static TreeElement* getNeededChild(const TreeElement* const element, const int key)
{
    return (element == NULL ? NULL : (key > element->key ? element->rightChild : element->leftChild));
}

int add(Tree* const tree, const int key, const char* const value)
{
    if (tree == NULL)
    {
        return nullPointerError;
    }
    TreeElement* current = tree->root;
    const char* const valueCopy = stringCopy(value);
    if (valueCopy == NULL)
    {
        return memoryError;
    }
    if (current == NULL)
    {
        TreeElement* newElement = (TreeElement*)calloc(1, sizeof(TreeElement));
        if (newElement == NULL)
        {
            return memoryError;
        }
        newElement->key = key;
        newElement->value = valueCopy;
        tree->root = newElement;
        return ok;
    }
    for (; getNeededChild(current, key) != NULL; current = getNeededChild(current, key));
    if (key == current->key)
    {
        free(current->value);
        current->value = valueCopy;
        return ok;
    }
    TreeElement* newElement = (TreeElement*)calloc(1, sizeof(TreeElement));
    if (newElement == NULL)
    {
        return memoryError;
    }
    newElement->key = key;
    newElement->value = valueCopy;
    if (key > current->key)
    {
        current->rightChild = newElement;
    }
    else
    {
        current->leftChild = newElement;
    }
    return ok;
}

static char* staticGet(const TreeElement* const node, const int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (key > node->key)
    {
        return staticGet(node->rightChild, key);
    }
    if (key < node->key)
    {
        return staticGet(node->leftChild, key);
    }
    return node->value;
}

char* get(const Tree* const tree, const int key)
{
    if (tree == NULL)
    {
        return NULL;
    }
    return staticGet(tree->root, key);
}

static TreeElement* deleteNode(const TreeElement* const node)
{
    if (node == NULL)
    {
        return node;
    }
    if (node->rightChild == NULL)
    {
        TreeElement* buffer = node->leftChild;;
        freeNode(node);
        return buffer;
    }
    if (node->rightChild->leftChild == NULL)
    {
        node->rightChild->leftChild = node->leftChild;
        TreeElement* buffer = node->rightChild;
        freeNode(node);
        return buffer;
    }
    TreeElement* previous = node;
    TreeElement* current = node->rightChild;
    for (; current->leftChild != NULL; current = current->leftChild)
    {
        previous = current;
    }
    previous->leftChild = current->rightChild;
    current->rightChild = node->rightChild;
    current->leftChild = node->leftChild;
    freeNode(node);
    return current;
}

static TreeElement* staticDelete(TreeElement* const node, const int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (key == node->key)
    {
        return deleteNode(node);
    }
    if (key > node->key)
    {
        node->rightChild = staticDelete(node->rightChild, key);
    }
    else
    {
        node->leftChild = staticDelete(node->leftChild, key);
    }
    return node;
}

bool delete(Tree* const tree, const int key)
{
    if (tree == NULL)
    {
        return true;
    }
    tree->root = staticDelete(tree->root, key);
    return false;
}

bool contains(const Tree* const tree, const int key, int* const errorCode)
{
    return get(tree, key, errorCode) != NULL;
}

static void deleteNodes(TreeElement* const node)
{
    if (node->rightChild != NULL)
    {
        deleteNodes(node->rightChild);
    }
    if (node->leftChild != NULL)
    {
        deleteNodes(node->leftChild);
    }
    freeNode(node);
}

void deleteTree(Tree** const tree)
{
    if ((*tree)->root != NULL)
    { 
        deleteNodes(((*tree)->root));
    }
    free(*tree);
    *tree = NULL;
}
