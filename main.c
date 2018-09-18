#include "parser.h"
#include "file_reader.h"

int main()
{
    FileReader *file = fropen("test.csv");
    if (file->file == 0)
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

    printf("Read with %d disk read operations\n", file->reads);

    return 0;
}