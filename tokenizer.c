#include "tokenizer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int skip_whitespaces(const char* src, int pos) {
    while (src[pos] && isspace(src[pos]))
    {
        pos++;
    }

    return pos; 
}

// Specifier for the token if it is a conditional statement
TokenType check_conditional_statement(const char* s) {
    if(strcmp(s, "if") == 0) {
        return T_IF;
    } 

    else if(strcmp(s, "else") == 0) {
        return T_ELSE;
    }

    else if(strcmp(s, "while") == 0) {
        return T_WHILE;
    }

    else if(strcmp(s, "for") == 0) {
        return T_FOR;
    }

    else {
        return T_IDENTIFIER;
    }
}


Token create_token(TokenType type, const char *value) {
    Token token;
    token.type = type;
    if (value)
        strncpy(token.value, value, MAX_LENGTH - 1);
    token.value[MAX_LENGTH - 1] = '\0';
    return token;
}

// Get the next token from a string
Token get_next_token(char* src, int* pos) {
    
    // Update position
    *pos = skip_whitespaces(src, *pos);

    // check for the EOF
    if(src[*pos] == '\0') {
        return create_token(T_EOF, "");
    }

    // Create a buffer
    char buffer[MAX_LENGTH] = {0};
    int buf_index = 0;

    char current = src[*pos];

    // If it is a digit
    if(isdigit(current)) {
        while(src[*pos] && isdigit(src[*pos]) && buf_index < MAX_LENGTH - 1) {
            buffer[buf_index++] = src[(*pos)++];
        }
        buffer[buf_index] = '\0';

        return create_token(T_NUMBER, buffer);
    }

    // Alphabetic
    if(isalpha(current)) {
        while(src[*pos] && isalnum(src[*pos]) && buf_index < MAX_LENGTH - 1) {
            buffer[buf_index++] = src[(*pos)++];
        }
        buffer[buf_index] = '\0';

        TokenType type = check_conditional_statement(buffer);

        return create_token(type, buffer);
    }

    // Single character, probably the arithmetic ones
    (*pos)++;

    switch (current)
    {
    case '+':
        return create_token(T_PLUS, "+");
    
    case '-':
        return create_token(T_MINUS, "-");
    
    case '*':
        return create_token(T_MUL, "*");
    
    case '/':
        return create_token(T_DIVIDE, "/");

    case '(': 
        return create_token(T_LPAREN, "(");
    
    case ')': 
        return create_token(T_RPAREN, ")");
        
    case '=': 
        return create_token(T_ASSIGN, "=");
        
    case ';': 
        return create_token(T_SEMI, ";");
        
    case ':': 
        return create_token(T_COLON, ":");

    case ',': 
        return create_token(T_COMMA, ",");
        
    default:  {
        char unknown_type[2];
        unknown_type[0] = current;
        unknown_type[1] = '\0';

        return create_token(T_UNKNOWN, unknown_type);
    }
        
    
    }



}

