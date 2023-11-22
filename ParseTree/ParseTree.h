#pragma once

// Abstract syntax tree struct
typedef struct ParseTree ParseTree;

// Build syntax treee
ParseTree* build(const char* const expression);

// Print tree in infix form
void printTree(const ParseTree* const tree);

// Calculating tree
int calculate(const ParseTree* const tree, int* const errorCode);

// Deleting tree
void deleteParseTree(ParseTree** tree);
