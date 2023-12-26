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

Tree* createTree(void)
{
    return (Tree*)calloc(1, sizeof(Tree));
}

static TreeElement* getNeededChild(const TreeElement* const element, const int key)
{
    return (element == NULL ? NULL : (key > element->key ? element->rightChild : element->leftChild));
}

static TreeElement* getParent(const Tree* const tree, const int key, int* const errorCode)
{
    if (tree == NULL)
    {
        *errorCode = nullPointerError;
        return NULL;
    }
    TreeElement* current = tree->root;
    if (current == NULL)
    {
        *errorCode = noSuchElement;
        return NULL;
    }
    if (current->key == key)
    {
        return NULL;
    }
    TreeElement* child = getNeededChild(current, key);
    for (; child != NULL && child->key != key; current = child);
    return current;
}

int add(Tree* const tree, const int key, const char* value)
{
    if (tree == NULL)
    {
        return nullPointerError;
    }
    TreeElement* current = tree->root;
    TreeElement* newElement = (TreeElement*)calloc(1, sizeof(TreeElement));
    if (newElement == NULL)
    {
        return memoryError;
    }
    newElement->key = stringCopy(key);
    if (newElement->key == NULL) {
        free(newElement);
        return memoryError;
    }
    newElement->value = stringCopy(value);
    if (newElement->value == NULL)
    {
        free(newElement->key);
        free(newElement);
        return memoryError;
    }
    if (current == NULL)
    {
        tree->root = newElement;
        return ok;
    }
    for (; getNeededChild(current, key) != NULL; current = getNeededChild(current, key));
    if (key == current->key)
    {
        free(current->value);
        current->value = stringCopy(value);
        if (current->value == NULL) {
            free(newElement->key);
            free(newElement->value);
            free(newElement);
            return memoryError;
        }
    }
    else if (key > current->key)
    {
        current->rightChild = newElement;
    }
    else
    {
        current->leftChild = newElement;
    }
    return ok;
}

char* get(const Tree* const tree, const int key, int* const errorCode)
{
    TreeElement* parent = getParent(tree, key, errorCode);
    if (*errorCode != ok)
    {
        if (*errorCode == noSuchElement)
        {
            *errorCode = ok;
        }
        return NULL;
    }
    TreeElement* child = getNeededChild(parent, key);
    return (parent == NULL) ? (tree->root->value) : 
        (child == NULL || child->key != key ? NULL : child->value);
}

static void setChild(Tree* const tree, TreeElement* const parent, const int key, const TreeElement* const newChild)
{
    if (parent == NULL)
    {
        tree->root = newChild;
        return;
    }
    if (key < parent->key)
    {
        parent->leftChild = newChild;
    }
    else
    {
        parent->rightChild = newChild;
    }
}

static TreeElement* deleteElementStatic(TreeElement* node, const char* key)
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


int delete(Tree* const tree, const int key)
{
    if (tree == NULL)
    {
        return nullPointerError;
    }
    if (tree->root == NULL)
    {
        return noSuchElement;
    }
    int errorCode = ok;
    TreeElement* parent = getParent(tree, key, &errorCode);
    if (errorCode != ok)
    {
        return errorCode;
    }
    TreeElement* element = (parent == NULL ? tree->root : getNeededChild(parent, key));
    if (element == NULL)
    {
        return noSuchElement;
    }
    if (element->leftChild == NULL)
    {
        setChild(tree, parent, key, element->rightChild);
        free(element);
        return ok;
    }
    if (element->leftChild->rightChild == NULL)
    {
        setChild(tree, parent, key, element->leftChild);
        free(element);
        return ok;
    }
    TreeElement* current = element->leftChild;
    TreeElement* previous = element->leftChild;
    for (; current->rightChild != NULL; previous = current, current = current->rightChild);
    previous->rightChild = NULL;
    setChild(tree, parent, key, current);
    free(element);
    return ok;
}

bool contains(const Tree* const tree, const int key, int* const errorCode)
{
    return get(tree, key, errorCode) != NULL;
}

static void deleteNodes(TreeElement** const node)
{
    if ((*node)->rightChild != NULL)
    {
        deleteNodes(&((*node)->rightChild));
    }
    if ((*node)->leftChild != NULL)
    {
        deleteNodes(&((*node)->leftChild));
    }
    free(*node);
}

void deleteTree(Tree** const tree)
{
    if ((*tree)->root != NULL)
    { 
        deleteNodes(&((*tree)->root));
    }
    free(*tree);
}
