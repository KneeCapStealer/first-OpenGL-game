#pragma once

#define DLL_EXPORT __declspec(dllexport)
typedef unsigned int GLenum;

GLenum InitEngine(void);

DLL_EXPORT void Run(void);
