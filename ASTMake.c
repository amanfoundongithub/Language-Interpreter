#include "ASTNode.h"
#include "ASTMake.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


ASTNode* create_integer_node(int number) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_NUMBER;
    node->number = number;

    return node; 
}

ASTNode* create_new_binary_node(ASTNode* left, ASTNode* right, TokenType op) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_BINARY;
    node->binary.left = left;
    node->binary.right = right;
    node->binary.op = op;

    return node; 
}

ASTNode* create_new_variable_node(const char* name) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_VAR;
    strncpy(node->var_name, name, sizeof(node->var_name) - 1);
    node->var_name[sizeof(node->var_name) - 1] = '\0';

    return node; 
}

ASTNode* create_assignment_node(const char* name, ASTNode* value) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_ASSIGNMENT;
    strncpy(node->assign.var_name, name, sizeof(node->assign.var_name) - 1);
    node->assign.var_name[sizeof(node->assign.var_name) - 1] = '\0';

    node->assign.value = value;

    return node; 
}

ASTNode* create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_IF;
    
    node->if_stmt.condition = condition;
    node->if_stmt.else_branch = else_branch;
    node->if_stmt.then_branch = then_branch;

    return node; 
}

ASTNode* create_while_node(ASTNode *cond, ASTNode *body) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_WHILE;
    
    node->while_stmt.condition = cond;
    node->while_stmt.body = body;

    return node; 
}

ASTNode* create_for_node(ASTNode *init, ASTNode *cond, ASTNode *post, ASTNode *body) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_FOR;
    
    node->for_stmt.cond = cond;
    node->for_stmt.body = body;
    node->for_stmt.init = init;
    node->for_stmt.post = post;

    return node; 
}

ASTNode* create_block_node(ASTNode** statements, int count) {

    // Malloc the node
    ASTNode* node = malloc(sizeof(ASTNode));

    if(!node) {
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }

    node->type = AST_BLOCK;
    
    node->block.statements = statements;
    node->block.count = count;

    return node; 
}