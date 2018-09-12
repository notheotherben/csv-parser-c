#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "linked_list.h"

typedef struct
{
    LinkedList *currentFields;
    LinkedList *headers;
    LinkedList *records;
} ParseContext;

// Public API
ParseContext *parseFile(FILE *file);

// Parser
void parseHeaders(FILE *file, ParseContext *ctx);
void parseRecords(FILE *file, ParseContext *ctx);
void parseRecord(FILE *file, ParseContext *ctx);
void parseFields(FILE *file, ParseContext *ctx);
void parseField(FILE *file, ParseContext *ctx);

// Tokenizer
const char *tokenizeString(FILE *file);
const char *tokenizeUnquotedString(FILE *file);
const char *tokenizeQuotedString(FILE *file);
void consume(FILE *file, char c);

#endif