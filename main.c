#include "parser.h"
#include <stdio.h>

int main()
{
    FILE *file = fopen("test.csv", "r");
    if (file == 0)
    {
        printf("Failed to open file\n");
        return 1;
    }

    ParseContext *ctx = parseFile(file);
    if (ctx->headers == LL_NULL)
    {
        printf("Failed to parse the file\n");
        return 2;
    }

    ll_print(ctx->headers, "%s\t");

    printf("\n");
    printf("-----------------------\n");

    LinkedListNode *cursor = ctx->records->head;

    while (cursor != LL_NULL)
    {
        ll_print(cursor->value, "%s\t");
        cursor = cursor->next;
        printf("\n");
    }

    return 0;
}