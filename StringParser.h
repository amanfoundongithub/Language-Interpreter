#ifndef STRING_PARSER_H_
#define STRING_PARSER_H_

#include "ASTMake.h"
#include "ASTNode.h"
#include "tokenizer.h"

ASTNode* parse_program(const char* source_str);

void delete_tree(ASTNode* node);

#endif 