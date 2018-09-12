#include "helpers.h"
#include "linked_list.h"
#include "parser.h"
#include "token.h"

ParseContext *parseFile(FILE *file)
{
    ParseContext *ctx = malloc(sizeof(ParseContext));
    ctx->currentFields = ll_new();
    ctx->headers = LL_NULL;
    ctx->records = ll_new();

    parseHeaders(file, ctx);
    parseRecords(file, ctx);
    return ctx;
}

void parseHeaders(FILE *file, ParseContext *ctx)
{
    parseFields(file, ctx);
    ctx->headers = ctx->currentFields;
    ctx->currentFields = ll_new();
    consume(file, '\n');
}

void parseRecords(FILE *file, ParseContext *ctx)
{
    while (!feof(file))
    {
        parseRecord(file, ctx);
    }
}

void parseRecord(FILE *file, ParseContext *ctx)
{
    parseFields(file, ctx);
    ll_append(ctx->records, ctx->currentFields);
    ctx->currentFields = ll_new();
    consume(file, '\n');
}

void parseFields(FILE *file, ParseContext *ctx)
{
    while (!feof(file) && fpeek(file) != '\n')
    {
        if (ctx->currentFields != LL_NULL && fpeek(file) == ',')
            consume(file, ',');

        parseField(file, ctx);
        consume(file, ' ');
    }
    consume(file, '\n');
}

void parseField(FILE *file, ParseContext *ctx)
{
    const char *str = tokenizeString(file);
    if (str == 0)
        return;
    ll_append(ctx->currentFields, str);
}

const char *tokenizeString(FILE *file)
{
    consume(file, ' ');

    if (feof(file))
        return 0;

    if (fpeek(file) == '"')
        return tokenizeQuotedString(file);

    return tokenizeUnquotedString(file);
}

const char *tokenizeQuotedString(FILE *file)
{
    consume(file, '"');

    Token *token = token_new();
    int c;
    while (!feof(file) && fpeek(file) != '"')
    {
        c = fgetc(file);

        if (c == '\\' && !feof(file))
        {
            int escape_sequence = fgetc(file);
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

const char *tokenizeUnquotedString(FILE *file)
{
    Token *token = token_new();
    while (!feof(file) && fpeek(file) != ',' && fpeek(file) != '\n')
        token_write(token, fgetc(file));

    const char *str = token_string(token);
    free(token);

    return str;
}

void consume(FILE *file, char c)
{
    if (feof(file))
        return;

    int fc;
    do
    {
        fc = fgetc(file);
    } while (c == fc && !feof(file));
    if (c != fc)
        ungetc(fc, file);
}