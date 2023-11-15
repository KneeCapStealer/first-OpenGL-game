#pragma once

#include "defines.h"

#include <stdbool.h>


DLL_USE bool WriteFile(const char* data, const char* fileName);

DLL_USE char* ReadFile(const char* fileName);

DLL_USE bool CopyFile(const char* fileName, const char* copiedName);
