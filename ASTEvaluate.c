#include "ASTEvaluate.h"
#include "Errors.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * @brief 
 * Stores the environment's variables 
 * 
 * @author amanfoundongithub 
 */
typedef struct
{
    char name[MAX_LENGTH_OF_WORD];
    int value;
} var;

/**
 * @brief Stores the values and the names of the
 * variables. 
 */
static var env[MAX_NUMBER_OF_VARIABLES];

/**
 * @brief Stores the count of the variables 
 * that are present in the environment currently. 
 */
static int env_count = 0;



/**
 * @brief Clears the environment to load new program 
 * 
 */
void clear_env(void){
    env_count = 0;                    // Clear the count
    memset(env, 0, sizeof(env));      // Clear the array 
}

/**
 * @brief Finds the variable in the environment 
 * 
 * @param name name of the variable 
 * @return var* a pointer to the location of variables
 *  
 */
var *find_variable_in_env(const char *name){
    for (int i = 0; i < env_count; i++){
        if (strcmp(name, env[i].name) == 0){
            return &env[i];
        }
    } return NULL;
}


/**
 * @brief Set the variable in the environment 
 * 
 * @param name name of the variable
 * @param value value to be set
 * 
 */
void set_variable_in_env(const char *name, int value){

    var *variable = find_variable_in_env(name);
    if (variable){
        variable->value = value;
    } else {
        if (env_count >= MAX_NUMBER_OF_VARIABLES){
            raise_too_many_variables_error();
        } else {
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

/**
 * @brief Utility function to evaluate an AST Node's value
 * 
 * @param node the AST node to be evaluated
 * @return the evaluated value
 */
int eval(ASTNode *node){
    if (!node){
        raise_node_not_provided_error();
    } else {
        switch (node->type){
            case AST_NUMBER:
                return node->number;

            case AST_VAR:{
                var *variable = find_variable_in_env(node->var_name);
                if (!variable){
                    raise_variable_not_defined_error();
                } else {
                    return variable->value;
                }
            }

            case AST_BINARY:{
                int left = eval(node->binary.left);
                int right = eval(node->binary.right);

                switch (node->binary.op){
                    case T_PLUS:
                        return left + right;

                    case T_MINUS:
                        return left - right;

                    case T_DIVIDE:{
                        if (right == 0){
                            raise_zero_division_error();
                        } else {
                            return left / right;
                        }
                    }

                    case T_MUL:
                        return left * right;

                    default:
                        raise_unsupported_operand();
                    }
                }

            default:
                raise_unsupported_operand();
            }
        return 0;
    }
}

/**
 * @brief Executes the statement that is dictated by the AST Node 
 * 
 * @param node the AST node to be executed 
 */
void exec(ASTNode* node) {
    if(!node) {
        return;
    }

    switch (node->type){
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
            } break;
        }

        case AST_WHILE: {
            while(eval(node->while_stmt.condition)) {
                exec(node->while_stmt.body);
            } break;
        }

        case AST_FOR: {
            exec(node->for_stmt.init);
            while(eval(node->for_stmt.cond)) {
                exec(node->for_stmt.body);
                exec(node->for_stmt.post);
            } break;
        }

        case AST_BLOCK: {
            for(int i = 0 ; i < node->block.count ; i++) {
                exec(node->block.statements[i]);
            } break; 
        }

        case AST_NUMBER:
        case AST_VAR:
        case AST_BINARY:
            (void)eval(node);
            break;
        
        default:
            raise_unsupported_statement();
    }
}

/**
 * @brief Runs an AST and executes the statements 
 * 
 * @param root the root of the AST Node
 */
void run(ASTNode * root) {
    clear_env();   // Clear the environment 
    exec(root);    // Execute the root  
}