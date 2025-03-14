
#include "StringParser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char* input; 

int position = 0;
static int *pos = &position; 

static Token current_token;

// Next token prediction
static void next_token(void) {
    current_token = get_next_token(input, pos);
}

// Parsers
static ASTNode* parse_expression(void);
static ASTNode* parse_term(void);
static ASTNode* parse_factor(void);
static ASTNode* parse_statement(void);

// Now define them below
static ASTNode* parse_factor(void) {

    ASTNode* node = NULL;
    
    if(current_token.type == T_NUMBER) {
        node = create_integer_node(atoi(current_token.value));
        next_token();
        return node;
    } else if(current_token.type == T_IDENTIFIER) {
        node = create_new_variable_node(current_token.value);
        next_token();
        return node;
    } else if(current_token.type == T_LPAREN) {
        next_token();
        node = parse_expression();
        if(current_token.type != T_RPAREN) {
            fprintf(stderr, "ERROR : Expected ')' for the corresponding '(");
            exit(EXIT_FAILURE);
        } else {
            next_token();
            return node;
        }
    } else {
        fprintf(stderr, "ERROR : Unexpected token type");
        exit(EXIT_FAILURE);
    }
}


static ASTNode* parse_term(void) {
    ASTNode* left = parse_factor();
    
    while(current_token.type == T_MUL || current_token.type == T_DIVIDE) {
        TokenType op = current_token.type;
        next_token();
        ASTNode* right = parse_factor();
        left = create_new_binary_node(left, right, op);
    }

    return left;
}

static ASTNode* parse_expression(void) {
    ASTNode* left = parse_term();
    while (current_token.type == T_PLUS || current_token.type == T_MINUS) {
        TokenType op = current_token.type;
        next_token();
        ASTNode* right = parse_term();
        left = create_new_binary_node(left, right, op);
    }
    return left;
}

static ASTNode* parse_statement(void) {

    if(current_token.type == T_IF) {
        next_token();
        ASTNode* condition = parse_expression();

        if(current_token.type != T_COLON) {
            fprintf(stderr, "ERROR : Expected ':' after if");
            exit(EXIT_FAILURE);
        } else {
            next_token();
            ASTNode* then_branch = parse_statement();

            if(current_token.type == T_SEMI) {
                next_token();
            }


            ASTNode* else_branch = NULL;

            if(current_token.type == T_ELSE) {
                next_token();
                if(current_token.type != T_COLON) {
                    fprintf(stderr, "ERROR : Expected ':' after else");
                    exit(EXIT_FAILURE);
                } else {
                    next_token();
                    else_branch = parse_statement();
                }
            }

            return create_if_node(condition, then_branch, else_branch);
        }
    } 
    else if(current_token.type == T_WHILE) {
        next_token(); 
        ASTNode* condition = parse_expression();
        if(current_token.type != T_COLON) {
            fprintf(stderr, "ERROR : Expected ':' after while");
            exit(EXIT_FAILURE);
        } else {
            next_token();
            ASTNode* body = parse_statement();
            return create_while_node(condition, body);
        }
    }
    else if(current_token.type == T_FOR) {
        next_token();
        ASTNode* init = parse_statement();
        if (current_token.type != T_SEMI) {
            fprintf(stderr, "Expected ';' after for initialization\n");
            exit(EXIT_FAILURE);
        } else {
            next_token();
            ASTNode* condition = parse_expression();
            if (current_token.type != T_SEMI) {
                fprintf(stderr, "Expected ';' after for condition\n");
                exit(EXIT_FAILURE);
            } else {
                next_token(); 
                ASTNode* post = parse_statement();
                if (current_token.type != T_COLON) {
                    fprintf(stderr, "Expected ':' after for post expression\n");
                    exit(EXIT_FAILURE);
                } else {
                    next_token(); 
                    ASTNode* body = parse_statement();
                    return create_for_node(init, condition, post, body);
                }
            }
        }
    }
    else if(current_token.type == T_IDENTIFIER) {
        Token id_token = current_token;
        next_token();
        if (current_token.type == T_ASSIGN) {
            next_token(); 
            ASTNode* expr = parse_expression();
            return create_assignment_node(id_token.value, expr);
        } else {
            fprintf(stderr, "Unexpected token after identifier: '%s'\n", current_token.value);
            exit(EXIT_FAILURE);
        }
    }
    else {
        return parse_expression();
    }
}

// parse_program: Parses a sequence of statements (separated by semicolons) until end-of-file.
ASTNode* parse_program(const char *source_str) {
    input = source_str;
    *pos = 0;
    next_token();


    ASTNode **statements = NULL;
    int count = 0;

    while (current_token.type != T_EOF) {
        ASTNode* stmt = parse_statement();
        
        statements = realloc(statements, sizeof(ASTNode*) * (count + 1));
        if (!statements) {
            fprintf(stderr, "Memory allocation error in parse_program\n");
            exit(EXIT_FAILURE);
        }
        statements[count++] = stmt;

        // If there is a semicolon
        if (current_token.type == T_SEMI) {
            next_token();
        } else {
            break;
        }
    }

    return create_block_node(statements, count);
}


void delete_tree(ASTNode* node) {
    if (!node) return; 

    switch (node->type) {
        case AST_NUMBER:
            // No dynamic memory to free for literals
            break;

        case AST_VAR:
            // Clear variable name if dynamically allocated (if applicable)
            memset(node->var_name, 0, sizeof(node->var_name));
            break;

        case AST_BINARY:
            delete_tree(node->binary.left);
            delete_tree(node->binary.right);
            break;

        case AST_ASSIGNMENT:
            delete_tree(node->assign.value);
            memset(node->assign.var_name, 0, sizeof(node->assign.var_name));
            break;

        case AST_IF:
            delete_tree(node->if_stmt.condition);
            delete_tree(node->if_stmt.then_branch);
            delete_tree(node->if_stmt.else_branch);
            break;

        case AST_WHILE:
            delete_tree(node->while_stmt.condition);
            delete_tree(node->while_stmt.body);
            break;

        case AST_FOR:
            delete_tree(node->for_stmt.init);
            delete_tree(node->for_stmt.cond);
            delete_tree(node->for_stmt.post);
            delete_tree(node->for_stmt.body);
            break;

        case AST_BLOCK:
            for (int i = 0; i < node->block.count; i++) {
                delete_tree(node->block.statements[i]);
            }
            free(node->block.statements); // Free the block array itself
            break;

        case AST_NOOP:
            // No operation, no resources to free
            break;

        default:
            fprintf(stderr, "Unknown AST Node type encountered during deletion.\n");
            break;
    }

    free(node); // Finally free the current node itself
}


