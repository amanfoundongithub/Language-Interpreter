#ifndef AST_NODE_H_
#define AST_NODE_H_

#include "SystemConstants.h"
#include "tokenType.h"

typedef enum {
    AST_NUMBER,
    AST_BINARY, 
    AST_VAR, 

    AST_ASSIGNMENT,
    
    AST_IF,
    AST_WHILE,
    AST_FOR,
    
    AST_BLOCK,
    AST_NOOP
} ASTType; 

typedef struct AST{
    ASTType type; 

    union {
        // Literal
        int number; 

        // Variable
        char var_name[MAX_LENGTH_OF_WORD];

        // Binary operation.
        struct {
            struct AST *left;
            struct AST *right;
            TokenType op;
        } binary;

        // Assignment: variable and value.
        struct {
            char var_name[MAX_LENGTH_OF_WORD];
            struct AST *value;
        } assign;

        // Branching statements
        struct {
            struct AST * condition;
            struct AST * else_branch;
            struct AST * then_branch;
        } if_stmt;

        // While loop
        struct {
            struct AST * condition;
            struct AST * body; 
        } while_stmt;

        // For loop
        struct {
            struct AST * init; 
            struct AST * cond;
            struct AST * post;
            struct AST * body;
        } for_stmt;

        // Block statements 
        struct {
            struct AST ** statements;
            int count;
        } block;
    };
} ASTNode; 

#endif 