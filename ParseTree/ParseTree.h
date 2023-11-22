#pragma once

// Abstract parse tree struct
typedef struct ParseTree ParseTree;

// Build syntax tree
ParseTree* build(const char* const expression);

// Print tree in infix form
void printTree(const ParseTree* const tree);

// Calculate expression
int calculate(const ParseTree* const tree, int* const errorCode);

// Delete tree
void deleteParseTree(ParseTree** tree);
