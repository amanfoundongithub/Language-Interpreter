#ifndef TOKEN_TYPE_H_
#define TOKEN_TYPE_H_

#define MAX_LENGTH 64

typedef enum {
    T_EOF,
    T_NUMBER,

    // Arithmetic operators
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIVIDE, 
    T_LPAREN,
    T_RPAREN, 
    T_ASSIGN, 
    T_IDENTIFIER, 
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
    char value[MAX_LENGTH];
} Token; 

#endif