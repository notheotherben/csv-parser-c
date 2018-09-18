#include "linked_list.h"
#include "parser.h"
#include "token.h"

ParseContext *parseFile(FileReader *file)
{
    ParseContext *ctx = malloc(sizeof(ParseContext));
    ctx->currentFields = ll_new();
    ctx->headers = LL_NULL;
    ctx->records = ll_new();

    parseHeaders(file, ctx);
    parseRecords(file, ctx);
    return ctx;
}

void parseHeaders(FileReader *file, ParseContext *ctx)
{
    parseFields(file, ctx);
    ctx->headers = ctx->currentFields;
    ctx->currentFields = ll_new();
    consume(file, '\n');
}

void parseRecords(FileReader *file, ParseContext *ctx)
{
    while (!freof(file))
    {
        parseRecord(file, ctx);
    }
}

void parseRecord(FileReader *file, ParseContext *ctx)
{
    parseFields(file, ctx);
    ll_append(ctx->records, ctx->currentFields);
    ctx->currentFields = ll_new();
    consume(file, '\n');
}

void parseFields(FileReader *file, ParseContext *ctx)
{
    while (!freof(file) && frpeek(file) != '\n')
    {
        if (ctx->currentFields != LL_NULL && frpeek(file) == ',')
            consume(file, ',');

        parseField(file, ctx);
        consume(file, ' ');
    }
    consume(file, '\n');
}

void parseField(FileReader *file, ParseContext *ctx)
{
    const char *str = tokenizeString(file);
    if (str == 0)
        return;
    ll_append(ctx->currentFields, str);
}

const char *tokenizeString(FileReader *file)
{
    consume(file, ' ');

    if (freof(file))
        return 0;

    if (frpeek(file) == '"')
        return tokenizeQuotedString(file);

    return tokenizeUnquotedString(file);
}

const char *tokenizeQuotedString(FileReader *file)
{
    consume(file, '"');

    Token *token = token_new();
    int c;
    while (!freof(file) && frpeek(file) != '"')
    {
        c = frget(file);

        if (c == '\\' && !freof(file))
        {
            int escape_sequence = frget(file);
            switch (escape_sequence)
            {
            case 'n':
                token_write(token, '\n');
                break;
            default:
                token_write(token, escape_sequence);
            }
        }
        else
        {
            token_write(token, c);
        }
    }

    consume(file, '"');

    const char *str = token_string(token);
    free(token);

    return str;
}

const char *tokenizeUnquotedString(FileReader *file)
{
    Token *token = token_new();
    while (!freof(file) && frpeek(file) != ',' && frpeek(file) != '\n')
        token_write(token, frget(file));

    const char *str = token_string(token);
    free(token);

    return str;
}

void consume(FileReader *file, char c)
{
    while (!freof(file) && frpeek(file) == c)
        frget(file);
}