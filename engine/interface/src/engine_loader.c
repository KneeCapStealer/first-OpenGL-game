// Source code
#include "engine.h"

// libraries
#include <assert.h>
#include <glfw3.h>
#include <sys/stat.h>
#include <windows.h>

// Must be below windows
#include <libloaderapi.h>

// Std lib
#include <stdio.h>
#include <stdlib.h>

// hotreload library
#include "hotreloading.h"

GLenum InitEngine(void)
{
    puts("Starting engine");
    HotReload();

    return EXIT_SUCCESS;
}

void ExitEngine(void)
{
    if (engineDLL)
    {
        if (!FreeLibrary(engineDLL))
            fputs("Couldn't free engine_dll.dll", stderr);
    }
}

void Run(void)
{
    HotReload();
    fp_run();
}
