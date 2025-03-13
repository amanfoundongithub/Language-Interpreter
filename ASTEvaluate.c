#include "ASTEvaluate.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Environment for storing variables
typedef struct
{
    char name[MAX_LENGTH_OF_WORD];
    int value;
} var;

static var env[MAX_NUMBER_OF_VARIABLES];
static int env_count = 0;

// Clear the entire environment.
void clear_env(void)
{
    env_count = 0;
    memset(env, 0, sizeof(env));
}

var *find_variable_in_env(const char *name)
{
    for (int i = 0; i < env_count; i++)
    {
        if (strcmp(name, env[i].name) == 0)
        {
            return &env[i];
        }
    }

    return NULL;
}

void set_variable_in_env(const char *name, int value)
{

    var *variable = find_variable_in_env(name);

    if (variable)
    {
        variable->value = value;
    }
    else
    {
        if (env_count >= MAX_NUMBER_OF_VARIABLES)
        {
            fprintf(stderr, "Environment Overflowed!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            strncpy(env[env_count].name, name, sizeof(env[env_count].name) - 1);
            env[env_count].name[sizeof(env[env_count].name) - 1] = '\0';
            env[env_count].value = value;
            env_count++;
        }
    }
}

// Helper: print the current environment.
void print_env(void) {
    printf("=== Environment ===\n");
    for (int i = 0; i < env_count; i++) {
        printf("%s = %d\n", env[i].name, env[i].value);
    }
}

// Evaluate an AST Node
int eval(ASTNode *node)
{
    if (!node)
    {
        fprintf(stderr, "ERROR : Node not provided, cannot evaluate!");
        exit(EXIT_FAILURE);
    }
    else
    {
        switch (node->type)
        {
        case AST_NUMBER:
            return node->number;

        case AST_VAR:
        {
            var *variable = find_variable_in_env(node->var_name);
            if (!variable)
            {
                fprintf(stderr, "ERROR : Variable not defined!");
                exit(EXIT_FAILURE);
            }
            else
            {
                return variable->value;
            }
        }

        case AST_BINARY:
        {
            int left = eval(node->binary.left);
            int right = eval(node->binary.right);

            switch (node->binary.op)
            {
            case T_PLUS:
                return left + right;

            case T_MINUS:
                return left - right;

            case T_DIVIDE:
            {
                if (right == 0)
                {
                    fprintf(stderr, "ERROR: Division by zero!");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    return left / right;
                }
            }

            case T_MUL:
                return left * right;

            default:
            {
                fprintf(stderr, "ERROR : Unsupported operand(s)");
                exit(EXIT_FAILURE);
            }
            }
        }

        default:
        {
            fprintf(stderr, "ERROR : Unsupported Operand(s)");
            exit(EXIT_FAILURE);
        }
        }

        return 0;
    }
}

// Execution
void exec(ASTNode* node) {
    if(!node) {
        return;
    }

    switch (node->type)
    {
    case AST_ASSIGNMENT: {
        int value = eval(node->assign.value);
        set_variable_in_env(node->assign.var_name, value);
        break;
    }

    case AST_IF: {
        if(eval(node->if_stmt.condition)) {
            exec(node->if_stmt.then_branch);
        } else {
            exec(node->if_stmt.else_branch);
        }
        break;
    }

    case AST_WHILE: {
        while(eval(node->while_stmt.condition)) {
            exec(node->while_stmt.body);
        }
        break;
    }

    case AST_FOR: {
        exec(node->for_stmt.init);
        while(eval(node->for_stmt.cond)) {
            exec(node->for_stmt.body);
            exec(node->for_stmt.post);
        }
        break;
    }

    case AST_BLOCK: {
        for(int i = 0 ; i < node->block.count ; i++) {
            exec(node->block.statements[i]);
        }

        break; 
    }

    case AST_NUMBER:
    case AST_VAR:
    case AST_BINARY:
        (void)eval(node);
        break;
        
    default:
        fprintf(stderr, "Unsupported statement type: %d\n", node->type);
        exit(EXIT_FAILURE);
    
    }
}

void run(ASTNode * root) {
    clear_env();
    exec(root); 
}

