// Source code
#include "loader.h"

// libraries
#include <assert.h>
#include <glfw3.h>
#include <sys/stat.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Must be below windows
#include <libloaderapi.h>

// Std lib
#include <stdio.h>
#include <stdlib.h>

// hotreload library
#include "hotreloading.h"

void InitEngine(void)
{
    puts("Starting engine");
    HotReload();
}

void Run(void)
{
    HotReload();
    fp_run();
}
