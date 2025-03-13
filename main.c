#include <stdio.h>
#include "tokenizer.h"

int main() {
    const char *src = "if x == 5: x = x + 1;";

    int pos = 0;
    Token token;

    // Get tokens until end-of-file.
    do {
        token = get_next_token(src, &pos);
        printf("Token: Type = %d, Lexeme = \"%s\"\n", token.type, token.value);
    } while (token.type != T_EOF);

    return 0;
}
