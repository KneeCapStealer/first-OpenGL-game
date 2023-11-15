#pragma once

// std lib
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// outside includes
#include <sys/stat.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// must be beneath windows.h
#include <libloaderapi.h>
#include <minwindef.h>
#include <synchapi.h>
#include <winbase.h>
// ------ library globals ------ //
typedef void (*fp_run_t)(void);
static fp_run_t fp_run;

// ------ lobrary functions ------ //
static inline time_t GetTimestamp(const char* fileName)
{
    struct stat outStat;
    if (stat(fileName, &outStat) == -1)
    {
        fprintf(stderr, "Failed to get the timestamp of %s, errno: %d", fileName, errno);
        return -1;
    }
    return outStat.st_mtime; // modified time
}

inline HMODULE LoadDLL(const char* fileName)
{
    HMODULE dll = LoadLibrary(fileName);
    if (!dll)
    {
        fprintf(stderr, "Failed to load library %s", fileName);
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

static inline void LoadFunctions(HMODULE dll) { fp_run = (fp_run_t)GetProcAddress(dll, "EX_Run"); }

static inline void HotReload(void)
{
    static time_t lastDllTime = 0;
    static HMODULE engineDLL = NULL;

    time_t currentDllTime = GetTimestamp("engine_dll.dll");
    if (currentDllTime != lastDllTime)
    {
        if (engineDLL)
        {
            if (!FreeDLL(engineDLL))
                fputs("Failed to properly free engineDLL", stderr);

            engineDLL = NULL;
        }

        if (!CopyFile("engine_dll.dll", "engine_dll_load.dll", FALSE))
        {
            fputs("Failed to load engine_dll.dll into engine_dll_load.dll", stderr);
            Sleep(10);
        }

        puts("Copied engine_dll.dll into engine_dll_load.dll");

        engineDLL = LoadDLL("engine_dll_load.dll");
        LoadFunctions(engineDLL);

        lastDllTime = currentDllTime;
    }
}
