#include <stdio.h>
#include <stdlib.h>
#include "ASTMake.h"


// Helper function to print AST nodes (for debugging).
void print_ast(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case AST_NUMBER:
            printf("Number: %d\n", node->number);
            break;

        case AST_VAR:
            printf("Variable: %s\n", node->var_name);
            break;

        case AST_BINARY:
            printf("Binary Operation:\n");
            print_ast(node->binary.left, indent + 1);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Operator: %d\n", node->binary.op);
            print_ast(node->binary.right, indent + 1);
            break;

        case AST_ASSIGNMENT:
            printf("Assignment:\n");
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Variable: %s\n", node->assign.var_name);
            print_ast(node->assign.value, indent + 1);
            break;

        case AST_IF:
            printf("If Statement:\n");
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->if_stmt.condition, indent + 2);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Then Branch:\n");
            print_ast(node->if_stmt.then_branch, indent + 2);
            if (node->if_stmt.else_branch) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Else Branch:\n");
                print_ast(node->if_stmt.else_branch, indent + 2);
            }
            break;

        case AST_WHILE:
            printf("While Loop:\n");
            print_ast(node->while_stmt.condition, indent + 1);
            print_ast(node->while_stmt.body, indent + 1);
            break;

        case AST_BLOCK:
            printf("Block:\n");
            for (int i = 0; i < node->block.count; i++) {
                print_ast(node->block.statements[i], indent + 1);
            }
            break;

        default:
            printf("Unknown node type\n");
            break;
    }
}

// Test cases
int main() {
    // Testing number node
    ASTNode *num_node = create_integer_node(42);

    // Testing variable node
    ASTNode *var_node = create_new_variable_node("x");

    // Testing binary operation
    ASTNode *binary_node = create_new_binary_node(create_integer_node(10), create_integer_node(20), T_PLUS);

    // Testing assignment
    ASTNode *assign_node = create_assignment_node("y", create_integer_node(100));

    // Testing if-else
    ASTNode *if_node = create_if_node(create_integer_node(1), create_integer_node(2), create_integer_node(3));

    // Testing block
    ASTNode *stmts[] = {num_node, var_node, binary_node, assign_node, if_node};
    ASTNode *block_node = create_block_node(stmts, 5);

    // Print the constructed AST
    printf("=== AST Test Output ===\n");
    print_ast(block_node, 0);

    // Free memory
    free(num_node);
    free(var_node);
    free(binary_node);
    free(assign_node);
    free(if_node);
    free(block_node);

    return 0;
}
