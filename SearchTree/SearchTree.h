#pragma once

#include <stdbool.h>

#include "errorCodes.h"

typedef struct Tree Tree;

int add(Tree* const tree, const int key, const char* const value);

bool delete(Tree* const tree, const int key);

char* get(const Tree* const tree, const int key);

bool contains(const Tree* const tree, const int key, int* const errorCode);

void deleteTree(Tree** const tree);

Tree* createTree(void);
