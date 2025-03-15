#ifndef TOKEN_TYPE_H_
#define TOKEN_TYPE_H_

#include "SystemConstants.h"

typedef enum {

    // End of file 
    T_EOF,

    // Number (assumed to be the only constants) 
    T_NUMBER,

    // Arithmetic operators
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIVIDE, 
    T_LPAREN,
    T_RPAREN, 

    // Assignment operator 
    T_ASSIGN, 

    // Identifier 
    T_IDENTIFIER, 
    
    // Semi colon 
    T_SEMI,

    // Conditional operators
    T_IF,
    T_ELSE,
    T_WHILE,
    T_FOR,
    T_COLON,
    T_COMMA,
    T_UNKNOWN 
} TokenType; 

typedef struct {
    TokenType type;
    char value[MAX_LENGTH_OF_WORD];
} Token; 

#endif