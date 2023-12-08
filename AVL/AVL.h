#pragma once
#include <stdbool.h>
typedef struct Tree Tree;
bool deleteElement(Tree* const tree, const char* key);
bool isContains(const Tree* const tree, const char* key);
int insert(Tree* const tree, const char* value, const char* key);
char* getValue(const Tree* const tree, const char* key);
Tree* createTree(void);
void deleteTree(Tree** const tree);
