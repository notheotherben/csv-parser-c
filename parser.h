#ifndef PARSER_H
#define PARSER_H

#include "file_reader.h"
#include "linked_list.h"

typedef struct
{
    LinkedList *currentFields;
    LinkedList *headers;
    LinkedList *records;
} ParseContext;

// Public API
ParseContext *parseFile(FileReader *file);

// Parser
void parseHeaders(FileReader *file, ParseContext *ctx);
void parseRecords(FileReader *file, ParseContext *ctx);
void parseRecord(FileReader *file, ParseContext *ctx);
void parseFields(FileReader *file, ParseContext *ctx);
void parseField(FileReader *file, ParseContext *ctx);

// Tokenizer
const char *tokenizeString(FileReader *file);
const char *tokenizeUnquotedString(FileReader *file);
const char *tokenizeQuotedString(FileReader *file);
void consume(FileReader *file, char c);

#endif