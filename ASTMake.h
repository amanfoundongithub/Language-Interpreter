#ifndef MAKE_AST_H_
#define MAKE_AST_H_

#include "ASTNode.h"

ASTNode* create_integer_node(int number);

ASTNode* create_new_binary_node(ASTNode* left, ASTNode* right, TokenType op);

ASTNode* create_new_variable_node(const char* name);

ASTNode* create_assignment_node(const char* name, ASTNode* value);

ASTNode* create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch);

ASTNode* create_while_node(ASTNode *cond, ASTNode *body);

ASTNode* create_for_node(ASTNode *init, ASTNode *cond, ASTNode *post, ASTNode *body);

ASTNode* create_block_node(ASTNode** statements, int count);

#endif 