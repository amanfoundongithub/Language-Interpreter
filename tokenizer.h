#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "tokenType.h"

int skip_whitespaces(const char* src, int pos);

TokenType check_conditional_statement(const char* s);

Token get_next_token(char* src, int* pos);

#endif