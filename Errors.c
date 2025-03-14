#include "Errors.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @brief Utility function to raise an error 
 * 
 * @param error 
 */
void raise_error(Error error) {
    fprintf(stderr, "%sERROR : %s\n" RESET, error.severity, error.error_message);
    exit(EXIT_FAILURE);
}

Error create_error(const char* message, const char* severity) {
    Error error;
    strcpy(error.error_message, message);
    strcpy(error.severity, severity);

    return error;
}

void raise_too_many_variables_error() {
    Error error = create_error("Too many variables in the environment!", YELLOW);
    raise_error(error);
}

void raise_node_not_provided_error() {
    Error error = create_error("No Node was provided, cannot evaluate. Aborted.", BLUE);
    raise_error(error);
}

void raise_variable_not_defined_error() {
    Error error = create_error("Unknown variable", YELLOW);
    raise_error(error);
}

void raise_zero_division_error() {
    Error error = create_error("Division by zero attempted.", RED);
    raise_error(error);
}

void raise_unsupported_operand() {
    Error error = create_error("Unsupported operand", RED);
    raise_error(error);
}

void raise_unsupported_statement() {
    Error error = create_error("Unsupported statement", GREEN);
    raise_error(error);
}
