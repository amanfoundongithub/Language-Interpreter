#ifndef ERRORS_H_
#define ERRORS_H_

typedef struct {
    // Message of the error 
    char error_message[200];
    
    // Severity
    char severity[10];
} Error;

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m" 


void raise_too_many_variables_error();
void raise_out_of_memory_error();

void raise_node_not_provided_error();
void raise_variable_not_defined_error();

void raise_zero_division_error();
void raise_unsupported_operand();

void raise_unsupported_statement();



#endif 