#pragma once

// std lib
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// outside includes
#include <sys/stat.h>
#include <windows.h>

// must be beneath windows.h
#include <libloaderapi.h>
#include <minwindef.h>
// ------ library globals ------ //
static HMODULE engineDLL;

typedef void (*fp_run_t)(void);
static fp_run_t fp_run;

// ------ lobrary functions ------ //
static inline time_t GetTimestamp(const char* filename)
{
    struct stat outStat;
    stat(filename, &outStat);
    return outStat.st_mtime; // modified time
}

inline HMODULE LoadDLL(const char* filename)
{
    HMODULE dll = LoadLibrary(filename);
    if (!dll)
    {
        fprintf(stderr, "Failed to load library %s", filename);
        return NULL;
    }

    return dll;
}

inline bool FreeDLL(HMODULE dll)
{
    BOOL result = FreeLibrary(dll);
    if (!result)
        fputs("Failed to free library", stderr);

    return (bool)result;
}

inline void LoadFunctions(void) {}

static inline void HotReload(void)
{
    static time_t lastDllTime;
    static HMODULE engineDLL;

    time_t currentDllTime = GetTimestamp("engine_dll.dll");
    if (currentDllTime != lastDllTime)
    {
        if (engineDLL)
        {
            if (!FreeDLL(engineDLL))
                fputs("Failed to properly free engineDLL", stderr);

            engineDLL = NULL;
        }

        // TODO: Copy the engine_dll.dll file into a new dll file so we can run and build at the
        // same time

        puts("Copied engine_dll.dll into engine_dll_load.dll");

        engineDLL = LoadDLL("engine_dll_load.dll");
        LoadFunctions();

        lastDllTime = currentDllTime;
    }
}
