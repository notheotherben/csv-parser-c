#ifndef FILE_H
#define FILE_H

#include <stdio.h>

typedef struct
{
    FILE *file;
    int current;
    int reads;
} FileReader;

FileReader *fropen(const char *name);

char frpeek(FileReader *file);
int freof(FileReader *file);
char frget(FileReader *file);

#endif