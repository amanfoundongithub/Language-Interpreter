#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "ASTNode.h"
#include "SystemConstants.h"

void run(ASTNode * root);

void print_env();

#endif