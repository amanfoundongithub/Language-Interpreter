#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "ASTNode.h"
#include "constants.h"


void run(ASTNode * root);

// Helper: print the current environment.
void print_env(void);
#endif