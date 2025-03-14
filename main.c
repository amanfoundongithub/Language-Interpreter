#include <stdio.h>
#include <stdlib.h>
#include "ASTMake.h"
#include "ASTEvaluate.h"
#include <string.h>
#include "StringParser.h"

// Function to read the entire file content into a string.
char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';  // Null-terminate the string.

    fclose(file);
    return buffer;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.python>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];

    // Ensure the file has a .python extension.
    const char* ext = strrchr(filename, '.');
    if (!ext || strcmp(ext, ".python") != 0) {
        fprintf(stderr, "Error: Expected a .python file\n");
        return EXIT_FAILURE;
    }

    // Read the file content.
    char* source_code = read_file(filename);
    printf("%s", source_code);

    // Parse and execute the program.
    ASTNode* root = parse_program(source_code);

    run(root);           
    print_env();         

    // // Clean up.
    free(source_code);
    delete_tree(root);      

    return EXIT_SUCCESS;
}