#include "helpers.h"

int fpeek(FILE *file)
{
    int c = fgetc(file);
    ungetc(c, file);
    return c;
}