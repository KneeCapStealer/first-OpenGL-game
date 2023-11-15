#include "defines.h"

// stdlib
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


DLL_EXPORT bool WriteFile(const char* data, const char* fileName)
{
    FILE* file = fopen(fileName, "wb");
    if (!file)
    {
        fprintf(stderr, "Failed to open file: %s", fileName);
        return false;
    }

    if (!fwrite(data, sizeof(char), strlen(data), file))
    {
        fprintf(stderr, "Failed to write %llu chars to file: %s", strlen(data), fileName);
        return false;
    }

    fclose(file);
    return true;
}

DLL_EXPORT char* ReadFile(const char* fileName)
{
    FILE* file = fopen(fileName, "rb");
    if (!file)
    {
        fprintf(stderr, "Failed to open file: %s", fileName);
        return NULL;
    }
    if (fseek(file, 0, SEEK_END) != 0) // navigate to the end of the file
    {
        fprintf(stderr, "Failed to find length of file: %s", fileName);
        return NULL;
    }

    off_t filesize = ftell(file);      // get the current position in the file (length)
    if (fseek(file, 0, SEEK_SET) != 0) // navigate to the beginning of file again
    {
        fprintf(stderr, "Failed to find length of file: %s", fileName);
        return NULL;
    }

    char* charBuf = malloc(filesize * sizeof(char));
    fread(charBuf, sizeof(char), filesize, file);
    fclose(file);

    return charBuf;
}

DLL_EXPORT bool CopyFile(const char* fileName, const char* copiedName)
{
    const char* data = ReadFile(fileName);
    if (!data)
        return false;

    if (!WriteFile(data, copiedName))
        return false;

    return true;
}
