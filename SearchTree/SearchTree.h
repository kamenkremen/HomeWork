#pragma once
#include <stdbool.h>
#include "errorCodes.h"
typedef struct Tree Tree;

int add(Tree* const tree, const int key, const char* value);
int delete(Tree* const tree, const int key);
char* get(const Tree* const tree, const int key, int* const errorCode);
bool contains(const Tree* const tree, const int key, int* const errorCode);
void deleteTree(Tree** tree);
Tree* createTree(void);
