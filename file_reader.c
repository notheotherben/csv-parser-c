#include <stdlib.h>
#include "file_reader.h"

FileReader *fropen(const char *name)
{
    FileReader *reader = malloc(sizeof(FileReader));
    reader->current = -1;
    reader->file = fopen(name, "r");
    reader->reads = 0;
    return reader;
}

int freof(FileReader *file)
{
    return file->current == -1 && feof(file->file);
}

char frpeek(FileReader *file)
{
    if (file->current == -1 && !feof(file->file))
    {
        file->reads++;
        file->current = fgetc(file->file);
    }

    return file->current;
}

char frget(FileReader *file)
{
    if (file->current == -1)
    {
        file->reads++;
        return fgetc(file->file);
    }

    int current = file->current;
    file->current = -1;
    return current;
}