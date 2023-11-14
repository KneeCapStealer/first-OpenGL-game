// Source code
#include "engine.h"

// libraries
#include <glfw3.h>
#include <windows.h>

// Std lib
#include <stdio.h>
#include <stdlib.h>

// ------ function pointers ------ //
typedef void (*fp_run_t)(void);
static fp_run_t fp_run;

// ------ global state ------ //
static HMODULE engineDLL;

GLenum InitEngine(void)
{
    puts("Starting engine");

    engineDLL = LoadLibrary("engine_dll.dll");
    if (!engineDLL)
    {
        puts("Could not load engine library");
        return EXIT_FAILURE;
    }

    fp_run = (fp_run_t)GetProcAddress(engineDLL, "EX_Run");
    if (!fp_run)
    {
        puts("Could not load function run");
        return EXIT_FAILURE;
    }

    printf("RUN function loaded, adress: %p", (void*)fp_run);

    fp_run();

    return EXIT_SUCCESS;
}

GLenum ExitEngine(void)
{
    if (engineDLL)
    {
        if (!FreeLibrary(engineDLL))
            fputs("Couldn't free engine_dll.dll", stderr);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Run(void)
{
    printf("RUN function RUN, adress: %p", (void*)fp_run);
    fp_run();
}
