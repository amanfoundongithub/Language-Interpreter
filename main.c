#include <stdio.h>
#include <stdlib.h>
#include "ASTMake.h"      // Functions for creating AST nodes
#include "ASTNode.h"      // AST node type declarations
#include "tokenType.h"    // Token types, e.g., T_PLUS, T_MINUS, etc.
#include "ASTEvaluate.h"  // Declares run() and print_env()

// Helper function to print a separator with a test name.
void print_separator(const char *test_name) {
    printf("\n=== %s ===\n", test_name);
}

int main() {
    //
    // Test 1: Simple Assignment: x = 5 + 3
    //
    {
        // Build: x = (5 + 3)
        ASTNode *expr = create_new_binary_node(
            create_integer_node(5),
            create_integer_node(3),
            T_PLUS
        );
        ASTNode *assign_x = create_assignment_node("x", expr);
        
        print_separator("Test 1: Simple Assignment (x = 5 + 3)");
        // Run the AST (this clears the environment before execution)
        run(assign_x);
        // Print the environment to verify that x was set correctly.
        print_env();
        
        // Free the allocated AST. (Assumes your AST memory management is handled)
        free(assign_x);
    }
    
    //
    // Test 2: If Statement: if (x) then y = (x * 2) else y = 0
    // First, set x = 10; then use its value as the condition.
    //
    {
        // Statement 1: x = 10
        ASTNode *assign_x = create_assignment_node("x", create_integer_node(10));
        // Statement 2: if (x) then y = (x * 2) else y = 0
        ASTNode *then_branch = create_assignment_node("y",
            create_new_binary_node(
                create_new_variable_node("x"),
                create_integer_node(2),
                T_MUL
            )
        );
        ASTNode *else_branch = create_assignment_node("y", create_integer_node(0));
        ASTNode *if_stmt = create_if_node(
            create_new_variable_node("x"),  // condition: x (nonzero is true)
            then_branch,
            else_branch
        );
        // Block both statements together.
        ASTNode *stmts[] = { assign_x, if_stmt };
        ASTNode *block = create_block_node(stmts, 2);
        
        print_separator("Test 2: If Statement (if(x) then y = x * 2 else y = 0)");
        run(block);
        print_env();
        
        free(block);
    }
    
    //
    // Test 3: While Loop: x = 5; while(x) { x = x - 1 }
    // This loop decrements x until it reaches 0.
    //
    {
        // Statement 1: x = 5
        ASTNode *assign_x = create_assignment_node("x", create_integer_node(5));
        // While loop: condition: x, body: x = x - 1
        ASTNode *while_body = create_assignment_node("x",
            create_new_binary_node(
                create_new_variable_node("x"),
                create_integer_node(1),
                T_MINUS
            )
        );
        ASTNode *while_loop = create_while_node(
            create_new_variable_node("x"),  // condition: x (nonzero => true)
            while_body
        );
        // Block: execute assignment then the while loop.
        ASTNode *stmts[] = { assign_x, while_loop };
        ASTNode *block = create_block_node(stmts, 2);
        
        print_separator("Test 3: While Loop (x = 5; while(x){ x = x - 1 })");
        run(block);
        print_env();
        
        free(block);
    }
    
    //
    // Test 4: For Loop: x = 0; for (i = 0; (3 - i); i = i + 1) { x = x + i }
    // Here the condition is built as (3 - i), which becomes 0 when i == 3.
    //
    {
        // Statement 1: x = 0
        ASTNode *assign_x = create_assignment_node("x", create_integer_node(0));
        // For loop components:
        ASTNode *init = create_assignment_node("i", create_integer_node(0));
        // Condition: (3 - i). When i becomes 3, (3 - 3) == 0 => false.
        ASTNode *condition = create_new_binary_node(
            create_integer_node(3),
            create_new_variable_node("i"),
            T_MINUS
        );
        // Post: i = i + 1
        ASTNode *post = create_assignment_node("i",
            create_new_binary_node(
                create_new_variable_node("i"),
                create_integer_node(1),
                T_PLUS
            )
        );
        // Body: x = x + i
        ASTNode *body = create_assignment_node("x",
            create_new_binary_node(
                create_new_variable_node("x"),
                create_new_variable_node("i"),
                T_PLUS
            )
        );
        // Create the for loop node.
        ASTNode *for_loop = create_for_node(init, condition, post, body);
        // Block both statements together.
        ASTNode *stmts[] = { assign_x, for_loop };
        ASTNode *block = create_block_node(stmts, 2);
        
        print_separator("Test 4: For Loop (x = 0; for(i = 0; 3-i; i = i + 1){ x = x + i })");
        run(block);
        print_env();
        
        free(block);
    }
    
    return 0;
}
