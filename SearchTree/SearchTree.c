#include <stdlib.h>
#include <stdio.h>

#include "SearchTree.h"

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

static TreeElement* getParent(const Tree* const tree, const int key, int* errorCode)
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
	for (; getNeededChild(current, key) != NULL && getNeededChild(current, key)->key != key; current = getNeededChild(current, key));
	return current;
}

int add(Tree* const tree, const int key, const char* value)
{
	if (tree == NULL)
	{
		return nullPointerError;
	}
	TreeElement* newElement = (TreeElement*)calloc(1, sizeof(TreeElement));
	if (newElement == NULL)
	{
		return memoryError;
	}
	newElement->key = key;
	newElement->value = value;
	TreeElement* current = tree->root;
	if (current == NULL)
	{
		tree->root = newElement;
		return ok;
	}
	for (; getNeededChild(current, key) != NULL; current = getNeededChild(current, key));
	if (key >= current->key)
	{
		current->rightChild = newElement;
	}
	else
	{
		current->leftChild = newElement;
	}
	return ok;
}

char* get(const Tree* const tree, const int key, int* errorCode)
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
	return (parent == NULL) ? (tree->root->value) : 
		(getNeededChild(parent, key) == NULL || getNeededChild(parent, key)->key != key ? NULL : getNeededChild(parent, key)->value);
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

bool contains(const Tree* const tree, const int key, int* errorCode)
{
	return get(tree, key, errorCode) != NULL;
}

static void deleteNodes(TreeElement** node)
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

void deleteTree(Tree** tree)
{
	if ((*tree)->root != NULL)
	{ 
		deleteNodes(&((*tree)->root));
	}
	free(*tree);
}
