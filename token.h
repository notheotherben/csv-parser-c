#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_SIZE 500

typedef struct
{
    char buffer[MAX_TOKEN_SIZE];
    int position;
} Token;

Token *token_new();
void token_write(Token *token, char c);
const char *token_string(Token *token);

#endif