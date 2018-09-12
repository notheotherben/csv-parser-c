#include "token.h"
#include <string.h>

Token *token_new()
{
    Token *token = (Token *)malloc(sizeof(Token));
    memset(token, 0, sizeof(Token));
    return token;
}

void token_write(Token *token, char c)
{
    token->buffer[token->position++] = c;
}

const char *token_string(Token *token)
{
    char *str = malloc(token->position + 1);
    strcpy(str, token->buffer);
    return str;
}